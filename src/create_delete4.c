/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_delete4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 22:06:53 by mehill            #+#    #+#             */
/*   Updated: 2022/04/08 22:07:16 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mrt.h"

t_hyperbloid	*new_hyperbloid(void)
{
	t_hyperbloid	*out;

	out = malloc(sizeof(t_hyperbloid));
	if (out == NULL)
		ft_exit("Error : could not allocate memory\n", NULL, 1);
	init_vect(&out->abc);
	out->k = -1;
	init_rgba(&out->color);
	return (out);
}

void	delete_hyperloid(t_hyperbloid **h)
{
	free(*h);
}

t_quadric	*new_quadric(void)
{
	t_quadric	*out;

	out = malloc(sizeof(t_quadric));
	if (out == NULL)
		ft_exit("Error : could not allocate memory\n", NULL, 1);
	init_vect(&out->xyz);
	init_vect(&out->xx);
	init_vect(&out->yy);
	init_vect(&out->zz);
	out->k = -1;
	init_rgba(&out->color);
	return (out);
}

void	delete_quadric(t_quadric **q)
{
	free(*q);
}

void	delete_world_objects(t_dlist **obj)
{
	t_dlist	*p;

	if (obj == NULL || *obj == NULL)
		return ;
	p = *obj;
	while (p)
	{
		delete_shape((t_shape **)&p->content);
		p = p->next;
	}
	ft_dlstclear(obj, NULL);
}
