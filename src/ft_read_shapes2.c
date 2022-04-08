/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_shapes2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 22:14:48 by mehill            #+#    #+#             */
/*   Updated: 2022/04/08 22:17:05 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mrt.h"

void	init_ambient(t_shape *s, char **spt)
{
	t_ambient	*l;

	if (!s || !spt || !spt[0] || !spt[1] || !spt[2])
		ft_exit("Error : not enough info for ", "Ambient !", 1);
	s->id = E_AMBIENT;
	l = new_ambient();
	l->ratio = ft_atod(spt[1]);
	if (l->ratio < 0 || l->ratio > 1)
		ft_exit("Error : ill formed value ", "Ambient ratio !", 1);
	if (init_rgba_str(&l->color, spt[2]) == 0)
		ft_exit("Error : ill formed color ", "Light !", 1);
	s->shape = l;
}

void	init_sphere(t_shape *s, char **spt)
{
	t_sphere	*l;

	printf("sp\n");
	if (!s || !spt || !spt[0] || !spt[1] || !spt[2] || !spt[3])
		ft_exit("Error : not enough info for ", "Sphere !", 1);
	s->id = E_SPHERE;
	l = new_sphere();
	if (init_point_str(&l->center, spt[1]) == 0)
		ft_exit("Error : ill formed point ", "Sphere center !", 1);
	l->diam = ft_atod(spt[2]);
	if (l->diam < 0)
		ft_exit("Error : ill formed value ", "Sphere diam !", 1);
	if (init_rgba_str(&l->color, spt[3]) == 0)
		ft_exit("Error : ill formed color ", "Sphere !", 1);
	s->shape = l;
}

void	init_plane(t_shape *s, char **spt)
{
	t_plane	*l;

	if (!s || !spt || !spt[0] || !spt[1] || !spt[2] || !spt[3])
		ft_exit("Error : not enough info for ", "Plane !", 1);
	s->id = E_PLANE;
	l = new_plane();
	if (init_point_str(&l->point, spt[1]) == 0)
		ft_exit("Error : ill formed point ", "Plane !", 1);
	if (init_vect_str(&l->normal, spt[2]) == 0)
		ft_exit("Error : ill formed vector ", "plane normal !", 1);
	if (init_rgba_str(&l->color, spt[3]) == 0)
		ft_exit("Error : ill formed color ", "plane !", 1);
	printf("plane color : %d %d %d\n", l->color.r, l->color.g, l->color.b);
	s->shape = l;
}

void	init_cylinder(t_shape *s, char **spt)
{
	t_cylinder	*l;

	if (!s || !spt || !spt[0] || !spt[1] || \
	!spt[2] || !spt[3] || !spt[4] || !spt[5])
		ft_exit("Error : not enough info for ", "Cylinder !", 1);
	s->id = E_CYLINDER;
	l = new_cylinder();
	if (init_point_str(&l->center, spt[1]) == 0)
		ft_exit("Error : ill formed point ", "Cylinder !", 1);
	if (init_vect_str(&l->normal, spt[2]) == 0)
		ft_exit("Error : ill formed vector ", "Cylinder normal !", 1);
	normalize(&l->normal);
	l->diam = ft_atod(spt[3]);
	if (l->diam < 0)
		ft_exit("Error : ill formed value ", "Cylinder diam !", 1);
	l->height = ft_atod(spt[4]);
	if (l->height < 0)
		ft_exit("Error : ill formed value ", "Cylinder height !", 1);
	if (init_rgba_str(&l->color, spt[5]) == 0)
		ft_exit("Error : ill formed color ", "Cylinder !", 1);
	s->shape = l;
}
