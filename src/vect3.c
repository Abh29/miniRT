/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:48:31 by mehill            #+#    #+#             */
/*   Updated: 2022/04/08 21:49:47 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mrt.h"


int	vect_diff(t_vect *a, t_vect *b, t_vect *diff)
{
	if (!a || !b || !diff)
		return (0);
	diff->x = a->x - b->x;
	diff->y = a->y - b->y;
	diff->z = a->z - b->z;
	diff->w = a->w - b->w;
	return (diff->w == 0 || diff->w == 1);
}

int	vect_scalar(t_vect *a, double k, t_vect *prod)
{
	if (!a || !prod)
		return (0);
	prod->x = a->x * k;
	prod->y = a->y * k;
	prod->z = a->z * k;
	prod->w = a->w * k;
	return (is_vect(prod));
}

double	vect_dot(t_vect *a, t_vect *b)
{
	if (!a || !b)
		return (INT_MAX);
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

t_vect	vect_cross(t_vect	*a, t_vect *b)
{
	t_vect	out;

	out = new_vect(a->y * b->z - a->z * b->y, \
		a->z * b->x - a->x * b->z, \
		a->x * b->y - a->y * b->x);
	return (out);
}

void	vect_cross2(t_vect	*a, t_vect *b, t_vect *out)
{
	write_vect(a->y * b->z - a->z * b->y, \
					a->z * b->x - a->x * b->z, \
					a->x * b->y - a->y * b->x, out);
	out->w = 0;
}
