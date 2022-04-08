/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_delete2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 22:02:45 by mehill            #+#    #+#             */
/*   Updated: 2022/04/08 22:03:08 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mrt.h"


t_ambient	*new_ambient(void)
{
	t_ambient	*out;

	out = malloc(sizeof(t_ambient));
	if (out == NULL)
		ft_exit("Error : could not allocate memory\n", NULL, 1);
	init_rgba(&out->color);
	out->ratio = -1;
	return (out);
}

void	delete_ambient(t_ambient **a)
{
	free(*a);
}

t_light	*new_light(void)
{
	t_light	*out;

	out = malloc(sizeof(t_light));
	if (out == NULL)
		ft_exit("Error : could not allocate memory\n", NULL, 1);
	out->ratio = -1;
	init_point(&out->center);
	init_rgba(&out->color);
	return (out);
}

void	delete_light(t_light **l)
{
	free(*l);
}

t_sphere	*new_sphere(void)
{
	t_sphere	*out;

	out = malloc(sizeof(t_sphere));
	if (out == NULL)
		ft_exit("Error : could not allocate memory\n", NULL, 1);
	init_point(&out->center);
	init_rgba(&out->color);
	out->diam = -1;
	return (out);
}
