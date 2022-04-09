/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_shapes3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 22:17:24 by mehill            #+#    #+#             */
/*   Updated: 2022/04/08 22:17:54 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mrt.h"

void	init_hyperbloid(t_shape *s, char **spt)
{
	if (!s || !spt || !spt[0] || !spt[1] || !spt[2])
		ft_exit("Error : not enough info for ", "Hyperbloid !", 1);
	(void)s;
	(void)spt;
}

void	init_quadratic(t_shape *s, char **spt)
{
	if (!s || !spt || !spt[0] || !spt[1] || !spt[2])
		ft_exit("Error : not enough info for ", "Quadratic !", 1);
	(void)s;
	(void)spt;
}

void	add_shape_info(t_shape *s, char *info)
{
	(void)s;
	(void)info;
}
