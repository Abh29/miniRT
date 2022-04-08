/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:51:26 by mehill            #+#    #+#             */
/*   Updated: 2022/04/08 21:52:00 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mrt.h"


int	nullvect(t_vect *v)
{
	if (v == NULL)
		return (1);
	if (fabs(v->x) < EPSILON)
		if (fabs(v->y) < EPSILON)
			if (fabs(v->z) < EPSILON)
				return (1);
	return (0);
}


int	vect_lin(t_vect *a, t_vect *b)
{
	if (a == NULL || b == NULL)
		return (1);
	if (nullvect(a) || nullvect(b))
		return (1);
	if (fabs(vect_dot(a, b) - vect_norm(a) * vect_norm(b)) < EPSILON)
		return (1);
	return (0);
}


int	dist_cmp(t_vect *a, t_vect *b, t_vect *cntr)
{
	if ((!a && !b) || !cntr)
		return (0);
	if (distance_ptpt(cntr, a) < distance_ptpt(cntr, b))
		return (1);
	else
		return (-1);
}

double	prjct_resolution(t_vect *a, t_vect *b)
{
	double	out;

	if (!a || !b)
		return (0);
	if (nullvect(a) || nullvect(b))
		return (0);
	out = vect_dot(a, b) / vect_dot(b, b);
	return (out);
}

void	vect_reflect(t_vect *in, t_vect *normal, t_vect *reflect)
{
	double	dot;

	if (!in || ! normal || !reflect)
		return ;
	dot = vect_dot(in, normal);
	reflect->x = in->x - 2 * normal->x * dot;
	reflect->y = in->y - 2 * normal->y * dot;
	reflect->z = in->z - 2 * normal->z * dot;
}
