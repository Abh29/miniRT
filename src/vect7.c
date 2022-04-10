/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:52:03 by mehill            #+#    #+#             */
/*   Updated: 2022/04/08 21:52:14 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mrt.h"


void	vect_cpy(t_vect *src, t_vect *dst)
{
	if (src == NULL || dst == NULL)
		return ;
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
	dst->w = src->w;
}

int	point_equ(t_vect *a, t_vect *b)
{
	if (fabs(a->x - b->x) < EPSILON)
		if (fabs(a->y - b->y) < EPSILON)
			if (fabs(a->z - b->z) < EPSILON)
				return (1);
	return (0);
}
