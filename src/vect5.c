/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:50:34 by mehill            #+#    #+#             */
/*   Updated: 2022/04/08 21:51:11 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mrt.h"


void	mid_point(t_vect *a, t_vect *b, t_vect *mid)
{
	if (!a || !b || !mid)
		return ;
	mid->x = (a->x + b->x) / 2;
	mid->y = (a->y + b->y) / 2;
	mid->z = (a->z + b->z) / 2;
}


int	init_vect_str(t_vect *v, char *str)
{
	char	**spt;

	if (v == NULL || str == NULL)
		return (0);
	spt = ft_split(str, ',');
	if (!spt || !spt[0] || !spt[1] || !spt[2])
		return (0);
	v->x = ft_atod(spt[0]);
	v->y = ft_atod(spt[1]);
	v->z = ft_atod(spt[2]);
	v->w = 0;
	ft_free_split(&spt);
	return (1);
}


int	init_point_str(t_vect *v, char *str)
{
	if (init_vect_str(v, str) == 0)
		return (0);
	v->w = 1;
	return (1);
}


void	normalize(t_vect *v)
{
	double	d;

	if (v == NULL || nullvect(v) || is_point(v))
		return ;
	d = vect_len(v);
	if (d < EPSILON)
		return ;
	v->x /= d;
	v->y /= d;
	v->z /= d;
}


double	vect_len(t_vect *v)
{
	double	out;

	out = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	return (out);
}
