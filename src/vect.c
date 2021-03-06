/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:45:47 by mehill            #+#    #+#             */
/*   Updated: 2022/04/08 21:52:37 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mrt.h"

t_vect	new_vect(double x, double y, double z)
{
	t_vect	out;

	write_vect(x, y, z, &out);
	out.w = 0;
	return (out);
}

t_vect	new_point(double x, double y, double z)
{
	t_vect	out;

	out = new_vect(x, y, z);
	out.w = 1;
	return (out);
}

void	init_vect(t_vect *v)
{
	if (v == NULL)
		return ;
	v->x = 0;
	v->y = 0;
	v->z = 0;
	v->w = 0;
}

void	init_point(t_vect *v)
{
	if (v == NULL)
		return ;
	v->x = 0;
	v->y = 0;
	v->z = 0;
	v->w = 1;
}
