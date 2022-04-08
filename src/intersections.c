/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:57:46 by mehill            #+#    #+#             */
/*   Updated: 2022/04/08 21:58:02 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mrt.h"

void	init_phong(t_phong *ph)
{
	if (ph == NULL)
		return ;
	init_rgba(&ph->ambient);
	init_rgba(&ph->diffuse.color);
	init_rgba(&ph->specular.color);
	ph->roughness = 50;
	ph->diffuse.ratio = 0.87;
	ph->specular.ratio = 0.4;
}

t_intrsct	*new_intersection_point(void)
{
	t_intrsct	*out;

	out = ft_allocate(1, sizeof(t_intrsct));
	init_vect(&out->normal);
	init_point(&out->point);
	init_rgba(&out->color);
	init_phong(&out->phong);
	out->dist = 0;
	out->s.shape = NULL;
	out->inside = 0;
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
	out = NULL;
	if (s->id == E_SPHERE)
		out = intr_sphere_vect((t_sphere *)s->shape, v, c);
	else if (s->id == E_PLANE)
		out = intr_plane_vect((t_plane *)s->shape, v, c);
	else if (s->id == E_CYLINDER)
		out = intr_cylinder_vect((t_cylinder *)s->shape, v, c);
	else if (s->id == E_HYPERBLOID)
		out = intr_hyperbloid_vect((t_hyperbloid *)s->shape, v, c);
	else if (s->id == E_QUADRATIC)
		out = intr_quadric_vect((t_quadric *)s->shape, v, c);
	return (out);
}

t_intrsct	*intr_light_vect(t_light *s, t_vect *v, t_camera *c)
{
	t_sphere	*tmp;
	t_intrsct	*out;

	return (NULL);
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
	double	t;

	if (equ == NULL)
		return ;
	equ->delta = equ->b * equ->b - 4 * equ->a * equ->c;
	if (equ->delta >= 0)
	{
		equ->x1 = (-1 * equ->b - sqrtl(equ->delta)) / (2 * equ->a);
		t = (- 1 * equ->b + sqrt(equ->delta)) / (2 * equ->a);
		if ((equ->x1 > t && t > 0) || equ->x1 < 0)
		{
			equ->x2 = equ->x1;
			equ->x1 = t;
		}
		else
			equ->x2 = t;
	}
}

double	descrimentant_sphere(t_sphere *s, t_vect *v, t_camera *cm, t_2deg_equ *equ)
{
	t_vect	direct;

	vect_diff(&cm->pov, &s->center, &direct);
	equ->a = vect_dot(v, v);
	equ->b = 2 * vect_dot(v, &direct);
	equ->c = vect_dot(&direct, &direct) - s->diam * s->diam;
	solve_2deg_equ(equ);
	return (equ->delta);
}

t_intrsct	*intr_sphere_vect1(t_sphere *s, t_vect *v, t_camera *c)
{
	t_2deg_equ	equ;
	t_intrsct	*out;
	t_vect		p;

	if (descrimentant_sphere(s, v, c, &equ) < 0)
		return (NULL);
	if (equ.x1 < 0 && equ.x2 < 0)
		return (NULL);
	out = new_intersection_point();
	out->dist = equ.x1;
	vect_scalar(v, equ.x1, &p);
	vect_sum(&c->pov, &p, &out->point);
	vect_diff(&out->point, &s->center, &out->normal);
	normalize(&out->normal);
	color_cpy(&s->color, &out->color);
//	out->dist = distance_ptpt(&c->pov, &out->point);
	return (out);
}

t_intrsct	*intr_sphere_vect2(t_sphere *s, t_vect *v, t_camera *c)
{
	t_2deg_equ	equ;
	t_intrsct	*out;
	t_vect	diff;
	double	p;
	double	diss;

	vect_diff(&c->pov, &s->center, &diff);
	p = vect_dot(v, &diff);
	diss = vect_dot(&diff, &diff) - (s->diam * s->diam);
	diss = p * p - diss;
	if (diss < 0)
		return (NULL);
	diss = sqrt(diss);
	equ.x1 = -p - diss;
	equ.x2 = -p + diss;
	if (equ.x1 < 0 && equ.x2 < 0)
		return (NULL);
	if (equ.x2 < equ.x1 && equ.x2 > 0)
		equ.x1 = equ.x2;
	out = new_intersection_point();
	out->dist = equ.x1;
	out->s.shape = s;
	out->s.id = E_SPHERE;
	return (out);
}


t_intrsct	*intr_sphere_vect(t_sphere *s, t_vect *v, t_camera *c)
{
	t_intrsct	*out;
	t_vect diff;
	t_vect t;
	double d_c;
	double d_t;
	
	vect_diff(&s->center, &c->pov, &diff);
	d_t = vect_dot(&diff, v);
	if (d_t < 0)
		return (NULL);
	t = new_point(v->x * d_t + c->pov.x, v->y * d_t + c->pov.y, v->z * d_t + c->pov.z);
	d_c = distance_ptpt(&s->center, &t);
	if (d_c > s->diam)
		return (NULL);
	out = new_intersection_point();
	out->dist = d_t - sqrt(s->diam * s->diam - d_c * d_c);
	out->s.shape = s;
	out->s.id = E_SPHERE;
	color_cpy(&s->color, &out->color); // delete this
	return (out);
}

t_intrsct	*intr_plane_vect1(t_plane *s, t_vect *v, t_camera *c)
{
	t_intrsct	*out;
	double		denom;
	t_vect		p;
	double		t;

	if (vect_lin(&s->normal, v))
		return (NULL);
	denom = vect_dot(v, &s->normal);
	if (fabs(denom) < EPSILON)
		return (NULL);
	vect_diff(&c->pov, &s->point, &p);
	t = vect_dot(&p, &s->normal) / denom;
	if (t < EPSILON)
		return (NULL);
	out = new_intersection_point();
	vect_scalar(v, t, &p);
	vect_sum(&c->pov, &p, &out->point);
	vect_scalar(&s->normal, 1, &out->normal);
	color_cpy(&s->color, &out->color);
	out->dist = distance_ptpt(&c->pov, &out->point);
	return (out);
}


t_intrsct	*intr_plane_vect(t_plane *s, t_vect *v, t_camera *c)
{
	t_intrsct	*out;
	double		denom;
	t_vect		p;
	double		t;

	if (vect_lin(&s->normal, v))
		return (NULL);
	denom = vect_dot(v, &s->normal);
	if (fabs(denom) < EPSILON)
		return (NULL);
	vect_diff(&s->point, &c->pov, &p);
	t = vect_dot(&p, &s->normal) / denom;
	if (t < EPSILON)
		return (NULL);
	out = new_intersection_point();
	out->dist = t;
	out->s.id = E_PLANE;
	color_cpy(&s->color, &out->color);
	out->s.shape = s;
	return (out);
}


t_intrsct	*intr_disk_vect(t_plane *s, t_vect *v, t_camera *c, double diam)
{
	t_intrsct	*out;
	double		tmp;

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

double	descrimentant_cylinder(t_cylinder *s, t_vect *v, t_camera *c, t_2deg_equ *equ)
{
	t_vect	tmpv;
	double	tmpf;
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
	double		d;

	if (fabs(descrimentant_cylinder(s, v, c, &equ)) < EPSILON || (equ.x1 < 0 && equ.x2 < 0))
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

t_intrsct	*intr_cylinder_vect2(t_cylinder *s, t_vect *v, t_camera *c)
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

t_intrsct	*intr_cylinder_vect(t_cylinder *s, t_vect *v, t_camera *c)
{
	t_intrsct	*out;
	t_vect	v2;
	t_vect	dp;
	t_vect tmp;
	t_2deg_equ	equ;

	vect_diff(&c->pov, &s->center, &dp);

	equ.delta = vect_dot(v, &s->normal);
	vect_scalar(&s->normal, equ.delta, &v2);
	vect_diff(v, &v2, &v2);
	equ.a = vect_dot(&v2, &v2);

	equ.delta = vect_dot(&dp, &s->normal);
	vect_scalar(&s->normal, equ.delta, &tmp);
	vect_diff(&dp, &tmp, &tmp);
	equ.b = 2 * vect_dot(&v2, &tmp);

	equ.c = vect_dot(&tmp, &tmp) - s->diam * s->diam;
	solve_2deg_equ(&equ);
	if(equ.delta < 0 || equ.x1 < 0)
		return (NULL);

	out = new_intersection_point();
	
	t_vect m;
	vect_scalar(v, equ.x1, &out->point);
	vect_sum(&out->point, &c->pov, &out->point);
	vect_diff(&out->point, &s->center, &m);
	double t = vect_dot(&m, &s->normal);
	if (t < 0 || s->height - t < 0)
	{
		equ.x1 = equ.x2;
		vect_scalar(v, equ.x1, &out->point);
		vect_sum(&out->point, &c->pov, &out->point);
		vect_diff(&out->point, &s->center, &m);
		t = vect_dot(&m, &s->normal);
		out->inside = 1;
		if (t < 0 || t > s->height)
		{
			delete_intersection_point(&out);
			return (NULL);
		}
	}
	color_cpy(&s->color, &out->color);
	out->s.id = E_CYLINDER;
	out->s.shape = s;
	out->dist = equ.x1;
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
