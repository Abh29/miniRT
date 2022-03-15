#include "../mrt.h"

t_intrsct		*new_intersection_point(void)
{
	t_intrsct	*out;

	out = ft_allocate(1, sizeof(t_intrsct));
	init_vect(&out->normal);
	init_point(&out->point);
	init_rgba(&out->color);
	out->dist = 0;
	return (out);
}

void			delete_intersection_point(t_intrsct **p)
{
	if (p == NULL || *p == NULL)
		return ;
	free(*p);
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

t_intrsct		*intr_light_vect(t_light *s, t_vect *v, t_camera *c)
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

float	descrimentant(t_sphere *s, t_vect *v, t_camera *cm, t_2deg_equ *equ)
{
	t_vect	*direct;
	float 	t;

	direct = new_vect(0, 0, 0);
	vect_diff(&s->center, &cm->pov, direct);
	equ->a = vect_dot(v, v);
	equ->b = 2 * vect_dot(v, direct);
	equ->c = vect_dot(direct, direct);
	delete_vect(&direct);
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
	return (equ->delta);
}

t_intrsct		*intr_sphere_vect(t_sphere *s, t_vect *v, t_camera *c)
{
	t_2deg_equ	equ;
	t_intrsct	*out;
	t_vect		p;

	if (descrimentant(s, v, c, &equ) < 0)
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

t_intrsct		*intr_plane_vect(t_plane *s, t_vect *v, t_camera *c)
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

t_intrsct		*intr_disk_vect(t_plane *s, t_vect *v, t_camera *c, float diam)
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

t_intrsct		*intr_cylinder_vect(t_cylinder *s, t_vect *v, t_camera *c)
{
	t_intrsct	*out;
	t_intrsct	*tp1;
	t_intrsct	*tp2;
	t_plane		*p1;

	p1 = new_plane();

	p1->point = s->center;
	p1->color = s->color;
	p1->normal = s->normal;
	tp1 = intr_disk_vect(p1, v, c, s->diam);
	vect_scalar(&p1->normal, s->height, &p1->normal);
	vect_sum(&p1->point, &p1->normal, &p1->point);
	p1->normal = s->normal;
	tp2 = intr_disk_vect(p1, v, c, s->diam);
	if (tp1 == NULL && tp2 == NULL)
		(void)out;
	return (NULL);
}

t_intrsct		*intr_hyperbloid_vect(t_hyperbloid *s, t_vect *v, t_camera *c)
{
	(void)s;
	(void)v;
	(void)c;
	return (NULL);
}

t_intrsct		*intr_quadric_vect(t_quadric *s, t_vect *v, t_camera *c)
{
	(void)s;
	(void)v;
	(void)c;
	return (NULL);
}




