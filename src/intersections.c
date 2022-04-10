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
	init_rgba(&ph->reflection);
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
	out->s = NULL;
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
	if (s->hide)
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
	else if (s->id == E_CONE)
		out = intr_cone_vect((t_cone *)s->shape, v, c);
	if (out)
		out->s = s;
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

void	ft_swap(double *a, double *b)
{
	double c;

	c = *a;
	*a = *b;
	*b = c;
}

t_intrsct	*intr_sphere_vect(t_sphere *s, t_vect *v, t_camera *c)
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
	if (equ.x1 < 0)
		ft_swap(&equ.x1, &equ.x2);
	out = new_intersection_point();
	out->inside =  equ.x2 < 0 ? 1 : 0;
	out->dist = equ.x1;
	return (out);
}

t_intrsct	*intr_sphere_vect3(t_sphere *s, t_vect *v, t_camera *c)
{
	t_intrsct	*out;
	t_vect diff;
	t_vect t;
	double d_c;
	double d_t;
	int in = 0;
	
	vect_diff(&s->center, &c->pov, &diff);
	if (vect_norm(&diff) < s->diam)
		in = 1;
	d_t = vect_dot(&diff, v);
	if (d_t < 0 && !in)
	 	return (NULL);
	t = new_point(v->x * d_t + c->pov.x, v->y * d_t + c->pov.y, v->z * d_t + c->pov.z);
	d_c = distance_ptpt(&s->center, &t);
	if (d_c > s->diam)
		return (NULL);
	out = new_intersection_point();
	out->dist = d_t - sqrt(s->diam * s->diam - d_c * d_c);
	if (in)
		out->dist = d_t + sqrt(s->diam * s->diam - d_c * d_c);
	out->inside = in;
	return (out);
}

t_intrsct	*intr_sphere_vect2(t_sphere *s, t_vect *v, t_camera *c)
{
	t_intrsct	*out;
	t_vect diff;
	t_vect t;
	t_vect F;
	double f;

	vect_diff(&s->center, &c->pov, &diff);
	normalize(&diff);
	t.x = vect_dot(&diff, v);
	vect_scalar(v, t.x, &F);
	vect_sum(&c->pov, &F, &F);
	f = distance_ptpt(&s->center, &F);
	if (f > s->diam)
	 	return (NULL);
	t.y = t.x - sqrt(s->diam * s->diam - f * f);
	t.z = t.x + sqrt(s->diam * s->diam - f * f);
	if (t.y < 0 && t.z < 0)
		return (NULL);
	out = new_intersection_point();
	if (t.y < 0)
	{
		ft_swap(&t.y, &t.z);
		out->inside = 1;
	}
	if (t.y < 0)
	{
		delete_intersection_point(&out);
		return (NULL);
	}
	out->dist = t.y;
	color_cpy(&s->color, &out->color); // delete this
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
	color_cpy(&s->color, &out->color);
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
	vect_cpy(&s->normal, &out->normal);
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
	out->dist = equ.x1;
	return (out);
}

t_intrsct		*intr_cone_vect(t_cone *s, t_vect *v, t_camera *c)
{
	t_2deg_equ equ;

	double sinn = sin(s->alfa);
	double coss = cos(s->alfa);

	double vn = vect_dot(v, &s->normal);
	t_vect dp;
	vect_diff(&c->pov, &s->center, &dp);
	double dpn = vect_dot(&dp, &s->normal);

	t_vect v_vn;
	vect_scalar(&s->normal, vn, &v_vn);
	vect_diff(v, &v_vn, &v_vn);

	t_vect dp_n;
	vect_scalar(&s->normal, dpn, &dp_n);
	vect_diff(&dp, &dp_n, &dp_n);

	equ.a = coss * coss * vect_dot(&v_vn, &v_vn) - sinn * sinn * vn * vn;
	
	equ.b = 2 * coss * coss * vect_dot(&v_vn, &dp_n) - 2 * sinn * sinn * vn * dpn;

	equ.c = coss * coss * vect_dot(&dp_n, &dp_n) - sinn * sinn * dpn * dpn;

	solve_2deg_equ(&equ);

	if(equ.delta < 0 || equ.x1 < 0)
		return (NULL);


	t_vect m;

	t_intrsct *out = new_intersection_point();
	vect_scalar(v, equ.x1, &out->point);
	vect_sum(&out->point, &c->pov, &out->point);
	vect_diff(&out->point, &s->center, &m);
	double t = vect_dot(&m, &s->normal) / coss;
	if (t < 0 || s->height - t < 0)
	{
		equ.x1 = equ.x2;
		vect_scalar(v, equ.x1, &out->point);
		vect_sum(&out->point, &c->pov, &out->point);
		vect_diff(&out->point, &s->center, &m);
		t = vect_dot(&m, &s->normal) / coss;
		out->inside = 1;
		if (t < 0 || t > s->height)
		{
			delete_intersection_point(&out);
			return (NULL);
		}
	}
	vect_scalar(&s->normal, t, &m);
	vect_diff(&out->point, &m, &out->normal);
	if (out->inside)
		vect_scalar(&out->normal, -1, &out->normal);
	normalize(&out->normal);
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
