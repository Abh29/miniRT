#include "../mrt.h"

void	transform_selected(t_dlist *obj, t_mat *trns, t_mat *scl, t_mat *rot)
{
	t_shape *s;

	if (obj == NULL)
		return ;
	while (obj)
	{
		s = obj->content;
		if (s->selected)
			transform_shape(s, trns, scl, rot);
		obj = obj->next;
	}
}

void	transform_shape(t_shape *s, t_mat *trns, t_mat *scl, t_mat *rot)
{
	if (!s)
		return ;
	if (s->id == E_SPHERE)
		transform_sphere((t_sphere *)s->shape, trns, scl, rot);
	else if (s->id == E_PLANE)
		transform_plane((t_plane *)s->shape, trns, scl, rot);
	else if (s->id == E_CYLINDER)
		transform_cylinder((t_cylinder *)s->shape, trns, scl, rot);
	else if (s->id == E_CONE)
		transform_cone((t_cone *)s->shape, trns, scl, rot);
	else if (s->id == E_HYPERBLOID)
		transform_hyperbloid((t_hyperbloid *)s->shape, trns, scl, rot);
	else if (s->id == E_QUADRATIC)
		transform_quadric((t_quadric *)s->shape, trns, scl, rot);
}


void	transform_sphere(t_sphere *s, t_mat *trns, t_mat *scl, t_mat *rot)
{
	t_vect	v;

	(void)rot;
	v = new_vect(1, 0, 0);
	if (scl)
	{
		v = mat_vect(scl, &v);
		s->diam = s->diam * vect_norm(&v);
	}
	if (trns)
		s->center = mat_vect(trns, &s->center);
}

void	transform_plane(t_plane *s, t_mat *trns, t_mat *scl, t_mat *rot)
{
	(void)scl;
	if (trns)
		s->point = mat_vect(trns, &s->point);
	if (rot)
	{
		s->normal = mat_vect(rot, &s->normal);
		normalize(&s->normal);
	}
}

void	transform_cylinder(t_cylinder *s, t_mat *trns, t_mat *scl, t_mat *rot)
{
	t_vect v;

	if (trns)
		s->center = mat_vect(trns, &s->center);
	if (rot)
	{
		s->normal = mat_vect(rot, &s->normal);
		normalize(&s->normal);
	}
	if (scl)
	{
		v = new_vect(s->height, 0, 0);
		v = mat_vect(scl, &v);
		s->height = vect_norm(&v);
	}
}

void	transform_quadric(t_quadric *s, t_mat *trns, t_mat *scl, t_mat *rot)
{
	(void)s;
	(void)trns;
	(void)rot;
	(void)scl;
}

void	transform_hyperbloid(t_hyperbloid *s, t_mat *trns, t_mat *scl, t_mat *rot)
{
	(void)s;
	(void)trns;
	(void)rot;
	(void)scl;
}

void	transform_cone(t_cone *s, t_mat *trns, t_mat *scl, t_mat *rot)
{
	t_vect v;

	if (trns)
		s->center = mat_vect(trns, &s->center);
	if (rot)
	{
		s->normal = mat_vect(rot, &s->normal);
		normalize(&s->normal);
	}
	if (scl)
	{
		v = new_vect(s->height, 0, 0);
		v = mat_vect(scl, &v);
		s->height = vect_norm(&v);
	}
}

