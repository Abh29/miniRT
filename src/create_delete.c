#include "../mrt.h"

t_shape			*new_shape(void)
{
	t_shape	*out;

	out = malloc(sizeof(t_shape));
	if (out == NULL)
		ft_exit("Error : could not allocate memory\n", NULL, 1);
	out->id = NULL;
	out->shape = NULL;
	return (out);
}

void			delete_shape(t_shape **s)
{
	t_shape *sh;

	if (s == NULL || *s == NULL || (*s)->id == NULL)
		return ;
	sh = *s;
	if (ft_strcmp(sh->id, "L") == 0)
		delete_light(&(sh->shape));
	else if (ft_strcmp(sh->id, "C") == 0)
		delete_camera(&sh->shape);
	else if (ft_strcmp(sh->id, "A") == 0)
		delete_ambient(&sh->shape);
	else if (ft_strcmp(sh->id, "sp") == 0)
		delete_sphere(&sh->shape);
	else if (ft_strcmp(sh->id, "pl") == 0)
		delete_plane(&sh->shape);
	else if (ft_strcmp(sh->id, "cy") == 0)
		delete_cylinder(&sh->shape);
	else if (ft_strcmp(sh->id, "hy") == 0)
		delete_hyperloid(&sh->shape);
	else if (ft_strcmp(sh->id, "qu") == 0)
		delete_quadric(&sh->shape);
	free(sh);
}

t_camera	*new_camera(void)
{
	t_camera	*out;

	out = malloc(sizeof(t_camera));
	if (out == NULL)
		ft_exit("Error : could not allocate memory\n", NULL, 1);
	out->fov = -1;
	init_vect(&out->normal);
	init_vect(&out->pov);
	return (out);
}

void			delete_camera(t_camera **c)
{
	free(*c);
}

t_ambient		*new_ambient(void)
{

	t_ambient	*out;

	out = malloc(sizeof(t_ambient));
	if (out == NULL)
		ft_exit("Error : could not allocate memory\n", NULL, 1);
	init_rgba(&out->color);
	out->ratio = -1;
	return (out);
}

void			delete_ambient(t_ambient **a)
{
	free(*a);
}

t_light			*new_light(void)
{
	t_light	*out;

	out = malloc(sizeof(t_light));
	if (out == NULL)
		ft_exit("Error : could not allocate memory\n", NULL, 1);
	out->ratio = -1;
	init_vect(&out->center);
	init_rgba(&out->color);
	return (out);
}

void			delete_light(t_light **l)
{
	free(*l);
}

t_sphere		*new_sphere(void)
{
	t_sphere	*out;

	out = malloc(sizeof(t_sphere));
	if (out == NULL)
		ft_exit("Error : could not allocate memory\n", NULL, 1);
	init_vect(&out->center);
	init_rgba(&out->color);
	out->diam = -1;
	return (out);
}

void			delete_sphere(t_sphere **sp)
{
	free(*sp);
}

t_plane			*new_plane(void)
{
	t_plane	*out;

	out = malloc(sizeof(t_plane));
	if (out == NULL)
		ft_exit("Error : could not allocate memory\n", NULL, 1);
	init_vect(&out->vect);
	init_vect(&out->normal);
	init_rgba(&out->color);
	return (out);
}

void			delete_plane(t_plane **pl)
{
	free(*pl);
}

t_cylinder		*new_cylinder(void)
{
	t_cylinder	*out;

	out = malloc(sizeof(t_cylinder));
	if (out == NULL)
		ft_exit("Error : could not allocate memory\n", NULL, 1);
	out->diam = -1;
	out->height = -1;
	init_vect(&out->center);
	init_vect(&out->normal);
	init_rgba(&out->color);
	return (out);
}

void			delete_cylinder(t_cylinder **cl)
{
	free(*cl);
}

t_hyperbloid	*new_hyperbloid(void)
{
	t_hyperbloid	*out;

	out = malloc(sizeof(t_hyperbloid));
	if (out == NULL)
		ft_exit("Error : could not allocate memory\n", NULL, 1);
	init_vect(&out->abc);
	out->k = -1;
	init_rgba(&out->color);
	return (out);
}

void			delete_hyperloid(t_hyperbloid **h)
{
	free(*h);
}

t_quadric		*new_quadric(void)
{
	t_quadric	*out;

	out = malloc(sizeof(t_quadric));
	if (out == NULL)
		ft_exit("Error : could not allocate memory\n", NULL, 1);
	init_vect(&out->xyz);
	init_vect(&out->xx);
	init_vect(&out->yy);
	init_vect(&out->zz);
	out->k = -1;
	init_rgba(&out->color);
	return (out);
}

void			delete_quadric(t_quadric **q)
{
	free(*q);
}
