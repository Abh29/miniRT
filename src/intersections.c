#include "../mrt.h"

t_intrsct	*new_intersection_point(void)
{
	t_intrsct	*out;

	out = ft_allocate(1, sizeof(t_intrsct));
	init_vect(&out->normal);
	init_point(&out->point);
	init_rgba(&out->color);
	out->dist = 0;
	return (out);
}

void	delete_intersection_point(t_intrsct **p)
{
	if (p == NULL || *p == NULL)
		return ;
	free(*p);
}

t_intrsct	*intersection_cpy(t_intrsct *p)
{
	t_intrsct	*out;

	if (p == NULL)
		return (NULL);
	out = new_intersection_point();
	ft_memcpy(out, p, sizeof(t_intrsct));
	return (out);
}

t_intrsct	*intr_shape_vect(t_shape *s, t_vect *v, t_camera *c)
{
	t_intrsct	*out;

	if (s == NULL || v == NULL || c == NULL)
		return (NULL);
	if (ft_strcmp(s->id, "L") == 0)
		out = intr_light_vect((t_light *)s->shape, v, c);
	else if (ft_strcmp(s->id, "sp") == 0)
		out = intr_sphere_vect((t_sphere *)s->shape, v, c);
	else if (ft_strcmp(s->id, "pl") == 0)
		out = intr_plane_vect((t_plane *)s->shape, v, c);
	else if (ft_strcmp(s->id, "cy") == 0)
		out = intr_cylinder_vect((t_cylinder *)s->shape, v, c);
	else if (ft_strcmp(s->id, "hy") == 0)
		out = intr_hyperbloid_vect((t_hyperbloid *)s->shape, v, c);
	else if (ft_strcmp(s->id, "qu") == 0)
		out = intr_quadric_vect((t_quadric *)s->shape, v, c);
	else
		return (NULL);
	return (out);
}

t_intrsct	*intr_light_vect(t_light *s, t_vect *v, t_camera *c)
{
	t_sphere	*tmp;
	t_intrsct	*out;

	tmp = new_sphere();
	tmp->center = s->center;
	tmp->color = s->color;
	tmp->diam = s->ratio;
	out = intr_sphere_vect(tmp, v, c);
	delete_sphere(&tmp);
	return (out);
}

void	solve_2deg_equ(t_2deg_equ *equ)
{
	float	t;

	if (equ == NULL)
		return ;
	equ->delta = equ->b * equ->b - 4 * equ->a * equ->c;
	if (equ->delta >= 0)
	{
		equ->x1 = (-equ->b - sqrtf(equ->delta)) / (2 * equ->a);
		t = (-equ->b + sqrtf(equ->delta)) / (2 * equ->a);
		if (equ->x1 > t && t > 0)
		{
			equ->x2 = equ->x1;
			equ->x1 = t;
		}
		else
			equ->x2 = t;
	}
}

float	descrimentant_sphere(t_sphere *s, t_vect *v, t_camera *cm, t_2deg_equ *equ)
{
	t_vect	*direct;

	direct = new_vect(0, 0, 0);
	vect_diff(&s->center, &cm->pov, direct);
	equ->a = vect_dot(v, v);
	equ->b = 2 * vect_dot(v, direct);
	equ->c = vect_dot(direct, direct) - s->diam * s->diam;
	delete_vect(&direct);
	solve_2deg_equ(equ);
	return (equ->delta);
}

t_intrsct	*intr_sphere_vect(t_sphere *s, t_vect *v, t_camera *c)
{
	t_2deg_equ	equ;
	t_intrsct	*out;
	t_vect		p;

	if (descrimentant_sphere(s, v, c, &equ) < 0)
		return (NULL);
	if (equ.x1 < 0 && equ.x2 < 0)
		return (NULL);
	out = new_intersection_point();
	vect_scalar(v, equ.x1, &p);
	vect_sum(&c->pov, &p, &out->point);
	vect_diff(&out->point, &s->center, &out->normal);
	normalize(&out->normal);
	color_cpy(&s->color, &out->color);
	out->dist = distance_ptpt(&c->pov, &out->point);
	return (out);
}

t_intrsct	*intr_plane_vect(t_plane *s, t_vect *v, t_camera *c)
{
	t_intrsct	*out;
	float		denom;
	t_vect		p;
	float		t;

	if (vect_lin(&s->normal, v))
		return (NULL);
	denom = vect_dot(v, &s->normal);
	if (denom < EPSILON)
		return (NULL);
	out = new_intersection_point();
	vect_diff(&c->pov, &s->point, &p);
	t = vect_dot(&p, &s->normal) / denom;
	vect_scalar(v, t, &p);
	vect_sum(&c->pov, &p, &out->point);
	vect_scalar(&s->normal, 1, &out->normal);
	color_cpy(&s->color, &out->color);
	out->dist = distance_ptpt(&c->pov, &out->point);
	return (out);
}

t_intrsct	*intr_disk_vect(t_plane *s, t_vect *v, t_camera *c, float diam)
{
	t_intrsct	*out;
	float		tmp;

	if (diam < EPSILON)
		return (NULL);
	out = intr_plane_vect(s, v, c);
	if (out == NULL)
		return (NULL);
	tmp = distance_ptpt(&out->point, &s->point);
	if (tmp - diam < EPSILON)
	{
		delete_intersection_point(&out);
		return (NULL);
	}
	return (out);
}

float	descrimentant_cylinder(t_cylinder *s, t_vect *v, t_camera *c, t_2deg_equ *equ)
{
	t_vect	tmpv;
	float	tmpf;
	t_vect	tmpv2;
	t_vect	p;

	tmpf = vect_dot(&s->normal, v);
	vect_scalar(&s->normal, tmpf, &tmpv);
	vect_diff(v, &tmpv, &tmpv);
	equ->a = vect_dot(&tmpv, &tmpv);
	vect_diff(&c->pov, &s->center, &p);
	tmpf = vect_dot(&p, &s->normal);
	vect_scalar(&s->normal, tmpf, &tmpv2);
	vect_diff(&p, &tmpv2, &tmpv2);
	equ->b = 2 * vect_dot(&tmpv, &tmpv2);
	tmpf = vect_dot(&tmpv2, &tmpv2);
	equ->c = tmpf * tmpf - s->diam * s->diam;
	solve_2deg_equ(equ);
	return (equ->delta);
}

t_intrsct	*closest_intersection(t_intrsct *a, t_intrsct *b, t_vect *cntr)
{
	t_intrsct	*out;
	int			t;

	if ((!a && !b) || !cntr)
		return (NULL);
	t = dist_cmp(&a->point, &b->point, cntr);
	if (t == 0)
		return (NULL);
	if (t > 0)
		out = intersection_cpy(a);
	else
		out = intersection_cpy(b);
	return (out);
}

t_intrsct	*intr_side_cylinder(t_cylinder *s, t_vect *v, t_camera *c)
{
	t_intrsct	*out;
	t_2deg_equ	equ;
	t_vect		x;
	t_vect		tmp;
	float		d;

	if (fabsf(descrimentant_cylinder(s, v, c, &equ)) < EPSILON || (equ.x1 < 0 && equ.x2 < 0))
		return (NULL);
	vect_scalar(v, equ.x1, &x);
	vect_sum(&c->pov, &x, &x);
	vect_diff(&x, &s->center, &tmp);
	d = prjct_resolution(&tmp, &s->normal);
	if (d < 0 || d > s->height)
		return (NULL);
	out = new_intersection_point();
	out->point = x;
	vect_scalar(&s->normal, d, &tmp);
	vect_sum(&s->center, &tmp, &tmp);
	vect_diff(&x, &tmp, &out->normal);
	normalize(&out->normal);
	color_cpy(&s->color, &out->color);
	return (out);
}

t_intrsct	*intr_cylinder_vect(t_cylinder *s, t_vect *v, t_camera *c)
{
	t_intrsct	*out;
	t_intrsct	*tp[4];
	t_plane		*pl;

	pl = new_plane();
	pl->point = s->center;
	pl->color = s->color;
	pl->normal = s->normal;
	tp[0] = intr_disk_vect(pl, v, c, s->diam);
	vect_scalar(&pl->normal, s->height, &pl->normal);
	vect_sum(&pl->point, &pl->normal, &pl->point);
	pl->normal = s->normal;
	tp[1] = intr_disk_vect(pl, v, c, s->diam);
	return(tp[0]);
	tp[2] = closest_intersection(tp[0], tp[1], &c->pov);
	//tp[2] = NULL;
	delete_intersection_point(&tp[0]);
	delete_intersection_point(&tp[1]);
	//tp[3] = intr_side_cylinder(s, v, c);
	tp[3] = NULL;
	out = closest_intersection(tp[2], tp[3], &c->pov);
	delete_intersection_point(&tp[3]);
	delete_intersection_point(&tp[2]);
	return (out);
}

t_intrsct	*intr_hyperbloid_vect(t_hyperbloid *s, t_vect *v, t_camera *c)
{
	(void)s;
	(void)v;
	(void)c;
	return (NULL);
}

t_intrsct	*intr_quadric_vect(t_quadric *s, t_vect *v, t_camera *c)
{
	(void)s;
	(void)v;
	(void)c;
	return (NULL);
}
