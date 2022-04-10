/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 22:01:16 by mehill            #+#    #+#             */
/*   Updated: 2022/04/08 22:02:33 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mrt.h"

t_shape	*new_shape(void)
{
	t_shape	*out;

	out = malloc(sizeof(t_shape));
	if (out == NULL)
		ft_exit("Error : could not allocate memory\n", NULL, 1);
	out->shape = NULL;
	out->c_pattern = E_NONE;
	out->transform = NULL;
	out->updated = 0;
	out->selected = 0;
	out->hide = 0;
	return (out);
}

void	delete_shape(t_shape **s)
{
	t_shape	*sh;

	if (s == NULL || *s == NULL || (*s)->shape == NULL)
		return ;
	sh = *s;
	if (sh->id == E_LIGHT)
		delete_light((t_light **) &(sh->shape));
	else if (sh->id == E_CAMERA)
		delete_camera((t_camera **) &sh->shape);
	else if (sh->id == E_AMBIENT)
		delete_ambient((t_ambient **) &sh->shape);
	else if (sh->id == E_SPHERE)
		delete_sphere((t_sphere **) &sh->shape);
	else if (sh->id == E_PLANE)
		delete_plane((t_plane **) &sh->shape);
	else if (sh->id == E_CYLINDER)
		delete_cylinder((t_cylinder **) &sh->shape);
	else if (sh->id == E_HYPERBLOID)
		delete_hyperloid((t_hyperbloid **) &sh->shape);
	else if (sh->id == E_QUADRATIC)
		delete_quadric((t_quadric **) &sh->shape);
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
	init_point(&out->pov);
	return (out);
}

void	set_up_vect(t_camera *c)
{
	t_vect	v;
	t_vect	right;

	v = new_vect(0, 0, 1);
	if (vect_lin(&c->normal, &v))
		write_vect(1, 1, 1, &v);
	right = vect_cross(&c->normal, &v);
	c->up = vect_cross(&c->normal, &right);
}

void	delete_camera(t_camera **c)
{
	free(*c);
}
