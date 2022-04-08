/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:52:54 by mehill            #+#    #+#             */
/*   Updated: 2022/04/08 21:53:22 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mrt.h"

t_mat	*create_mat(int n, int m)
{
	t_mat	*out;
	int		i;

	out = ft_allocate(1, sizeof(t_mat));
	out->n = n;
	out->m = m;
	out->data = ft_allocate(n + 1, sizeof(double *));
	i = 0;
	while (i < n)
		out->data[i++] = ft_allocate(m , sizeof(double));
	out->data[i] = NULL;
	return (out);
}

void	delete_mat(t_mat **m)
{
	int	i;

	if (!m || !*m)
		return ;
	i = 0;
	while (i < (*m)->n)
		free((*m)->data[i++]);
	free((*m)->data);
	free(*m);
}

t_mat	*mat_sum(t_mat *a, t_mat *b)
{
	t_mat	*out;
	int		i;
	int		j;

	if (!a || !b)
		return (NULL);
	if (a->n != b->n || a->m != b->m)
		return (NULL);
	out = create_mat(a->n, a->m);
	i = 0;
	while (i < a->n)
	{
		j = 0;
		while (j < a->m)
		{
			out->data[i][j] = a->data[i][j] + b->data[i][j];
			j++;
		}
		i++;
	}
	out->data[i] = NULL;
	return (out);
}

t_mat	*mat_diff(t_mat *a, t_mat *b)
{
	t_mat	*out;
	int		i;
	int		j;

	if (!a || !b)
		return (NULL);
	if (a->n != b->n || a->m != b->m)
		return (NULL);
	out = create_mat(a->n, a->m);
	i = 0;
	while (i < a->n)
	{
		j = 0;
		while (j < a->m)
		{
			out->data[i][j] = a->data[i][j] - b->data[i][j];
			j++;
		}
		i++;
	}
	out->data[i] = NULL;
	return (out);
}

t_mat	*mat_scal(t_mat *a, double k)
{
	t_mat	*out;
	int		i;
	int		j;

	if (!a)
		return (NULL);
	out = create_mat(a->n, a->m);
	i = 0;
	while (i < a->n)
	{
		j = 0;
		while (j < a->m)
		{
			out->data[i][j] = a->data[i][j] * k;
			j++;
		}
		i++;
	}
	out->data[i] = NULL;
	return (out);
}
