/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_delete3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 22:03:21 by mehill            #+#    #+#             */
/*   Updated: 2022/04/08 22:06:29 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mrt.h"

void	delete_sphere(t_sphere **sp)
{
	free(*sp);
}

t_plane	*new_plane(void)
{
	t_plane	*out;

	out = malloc(sizeof(t_plane));
	if (out == NULL)
		ft_exit("Error : could not allocate memory\n", NULL, 1);
	init_point(&out->point);
	init_vect(&out->normal);
	init_rgba(&out->color);
	return (out);
}

void	delete_plane(t_plane **pl)
{
	free(*pl);
}

t_cylinder	*new_cylinder(void)
{
	t_cylinder	*out;

	out = malloc(sizeof(t_cylinder));
	if (out == NULL)
		ft_exit("Error : could not allocate memory\n", NULL, 1);
	out->diam = -1;
	out->height = -1;
	init_point(&out->center);
	init_vect(&out->normal);
	init_rgba(&out->color);
	return (out);
}

void	delete_cylinder(t_cylinder **cl)
{
	free(*cl);
}
