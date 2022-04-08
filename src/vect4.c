/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:49:58 by mehill            #+#    #+#             */
/*   Updated: 2022/04/08 21:50:31 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mrt.h"


void	delete_vect(t_vect **v)
{
	free(*v);
}

double	distance_ptpt(t_vect *a, t_vect *b)
{
	double	out;

	if (!a || !b)
		return (INT_MAX);
	out = (b->x - a->x) * (b->x - a->x);
	out += (b->y - a->y) * (b->y - a->y);
	out += (b->z - a->z) * (b->z - a->z);
	return (sqrt(out));
}

double	vect_norm(t_vect *v)
{
	if (v == NULL)
		return (INT_MAX);
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}	

double	distance_ptln(t_vect *a, t_vect *b, t_vect *normal)
{
	t_vect	diff;

	if (!a || !b || !normal)
		return (INT_MAX);
	vect_diff(b, a, &diff);
	return (vect_dot(&diff, normal) / vect_norm(normal));
}

double	distance_ptp(t_vect *a, t_plane	*p)
{
	double	out;

	if (!a || !p)
		return (INT_MAX);
	out = p->normal.x * a->x + p->normal.y * a->y + p->normal.z * a->z;
	out += vect_dot(&p->normal, &p->point);
	if (out < 0)
		out *= -1;
	return (out / vect_norm(&p->normal));
}
