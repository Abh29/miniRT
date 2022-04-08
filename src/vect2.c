/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:47:47 by mehill            #+#    #+#             */
/*   Updated: 2022/04/08 21:48:21 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mrt.h"

int	is_point(t_vect *v)
{
	if (!v)
		return (0);
	return (v->w == 1);
}

int	is_vect(t_vect *v)
{
	if (!v)
		return (0);
	return (v->w == 0);
}

void	write_vect(double x, double y, double z, t_vect *v)
{
	if (v == NULL)
		return ;
	v->x = x;
	v->y = y;
	v->z = z;
	v->w = 0;
}

void	write_point(double x, double y, double z, t_vect *v)
{
	if (v == NULL)
		return ;
	v->x = x;
	v->y = y;
	v->z = z;
	v->w = 1;
}

int	vect_sum(t_vect *a, t_vect *b, t_vect *sum)
{
	if (!a || !b || !sum)
		return (0);
	sum->x = a->x + b->x;
	sum->y = a->y + b->y;
	sum->z = a->z + b->z;
	sum->w = a->w + b->w;
	return (sum->w == 0 || sum->w == 1);
}
