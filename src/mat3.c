/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:55:47 by mehill            #+#    #+#             */
/*   Updated: 2022/04/08 21:56:18 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mrt.h"

t_mat	*sub_mat(t_mat *a, int line, int col)
{
	t_mat	*out;
	int		i;
	int		j;
	int		k;
	int		l;

	if (!a || a->m < 2 || a->n < 2)
		return (NULL);
	if (line < 0 || line >= a->n || col < 0 || col >= a->m)
		return (NULL);
	out = create_mat(a->n - 1, a->m - 1);
	i = 0;
	l = 0;
	while (l < a->n - 1)
	{
		if (i == line)
			i++;
		j = 0;
		k = 0;
		while (k < a->m - 1)
		{
			if (j == col)
				j++;
			out->data[l][k] = a->data[i][j];
			j++;
			k++;
		}
		i++;
		l++;
	}
	return (out);
}

double	det_mat(t_mat *a)
{
	double	det;
	t_mat	*tmp;
	int		s;
	int		i;

	if (!a || a->n != a->m)
		ft_exit("Error : determinant of non square matrix !\n", NULL, 1);
	if (a->n == 2)
	{
		det = a->data[0][0] * a->data[1][1] - a->data[1][0] * a->data[0][1];
		return (det);
	}
	det = 0;
	s = 1;
	i = 0;
	while (i < a->n)
	{
		tmp = sub_mat(a, 0, i);
		det += s * det_mat(tmp) * a->data[0][i];
		delete_mat(&tmp);
		s *= -1;
		i++;
	}
	return (det);
}


t_mat	*rev_mat(t_mat *a)
{
	double	det;
	t_mat	*out;
	int		i;
	int		j;
	t_mat	*tmp;

	if (!a || a->n != a->m)
		ft_exit("Error : inverse of non square matrix !\n", NULL, 1);
	det = det_mat(a);
	if (fabs(det) < EPSILON)
		ft_exit("Error : matrix in not inversible det = 0 !", NULL, 1);
	out = create_mat(a->n, a->m);
	i = 0;
	while (i < a->n)
	{
		j = 0;
		while (j < a->m)
		{
			tmp = sub_mat(a, i, j);
			out->data[i][j] = pow(-1, i + j) * det_mat(tmp) / det;
			delete_mat(&tmp);
			j++;
		}
		i++;
	}
	tmp = transpose(out);
	delete_mat(&out);
	return (tmp);
}
