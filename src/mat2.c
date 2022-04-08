/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:53:39 by mehill            #+#    #+#             */
/*   Updated: 2022/04/08 21:55:38 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mrt.h"


t_mat	*mat_mult(t_mat *a, t_mat *b)
{
	t_mat	*out;
	int		i;
	int		j;
	int		k;

	if (!a || !b || a->m != b->n)
		return (NULL);

	out = create_mat(a->n, b->m);
	i = 0;
	while (i < a->n)
	{
		j = 0;
		while (j < b->m)
		{
			k = 0;
			out->data[i][j] = 0;
			while (k < a->m)
			{
				out->data[i][j] += a->data[i][k] * b->data[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	out->data[i] = NULL;
	return (out);
}

t_vect	mat_vect(t_mat *a, t_vect *v)
{
	t_vect	out;
	double	**f;

	out = new_vect(0, 0, 0);
	f = a->data;
	out.x = f[0][0] * v->x + f[0][1] * v->y + f[0][2] * v->z + f[0][3] * v->w;
	out.y = f[1][0] * v->x + f[1][1] * v->y + f[1][2] * v->z + f[1][3] * v->w;
	out.z = f[2][0] * v->x + f[2][1] * v->y + f[2][2] * v->z + f[2][3] * v->w;
	out.w = f[3][0] * v->x + f[3][1] * v->y + f[3][2] * v->z + f[3][3] * v->w;
	return (out);
}

t_vect	vect_mat(t_vect *v, t_mat *a)
{
	t_vect	out;
	double	**f;

	out = new_vect(0, 0, 0);
	f = a->data;
	out.x = f[0][0] * v->x + f[1][0] * v->y + f[2][0] * v->z + f[3][0] * v->w;
	out.y = f[0][1] * v->x + f[1][1] * v->y + f[2][1] * v->z + f[3][1] * v->w;
	out.z = f[0][2] * v->x + f[1][2] * v->y + f[2][2] * v->z + f[3][2] * v->w;
	out.w = f[0][3] * v->x + f[1][3] * v->y + f[2][3] * v->z + f[3][3] * v->w;
	return (out);
}

t_mat	*indentity(int n)
{
	t_mat	*out;
	int		i;
	int		j;

	if (n < 1)
		return (NULL);
	out = create_mat(n, n);
	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < n)
		{
			if (i == j)
				out->data[i][j] = 1;
			else
				out->data[i][j] = 0;
			j++;
		}
		i++;
	}
	out->data[i] = NULL;
	return (out);
}

t_mat	*transpose(t_mat *a)
{
	t_mat	*out;
	int		i;
	int		j;

	if (!a)
		return (NULL);
	out = create_mat(a->m, a->n);
	i = 0;
	while (i < a->n)
	{
		j = 0;
		while (j < a->m)
		{
			out->data[j][i] = a->data[i][j];
			j++;
		}
		i++;
	}
	return (out);
}
