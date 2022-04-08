/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 22:00:19 by mehill            #+#    #+#             */
/*   Updated: 2022/04/08 22:00:38 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mrt.h"


int	color_to_int(t_rgba *c)
{
	int	out;

	if (!c)
		return (0);
	out = c->a;
	out = (out << 8) + c->r;
	out = (out << 8) + c->g;
	out = (out << 8) + c->b;
	return (out);
}

void	int_to_color(int rgb, t_rgba *c)
{
	if (!c)
		return ;
	c->a = (rgb >> 24) & 0xFF;
	c->r = (rgb >> 16) & 0xFF;
	c->g = (rgb >> 8) & 0xFF;
	c->b = rgb & 0xFF;
}


int	init_rgba_str(t_rgba *c, char *str)
{
	char	**spt;

	if (c == NULL || str == NULL)
		return (0);
	spt = ft_split(str, ',');
	if (!spt || !spt[0] || !spt[1] || !spt[2])
		return (0);
	c->r = ft_atoi(spt[0]);
	c->g = ft_atoi(spt[1]);
	c->b = ft_atoi(spt[2]);
	if (spt[3])
		c->a = ft_atod(spt[3]);
	else
		c->a = 1;
	ft_free_split(&spt);
	return (1);
}

void	color_cpy(t_rgba *c, t_rgba *cpy)
{
	if (c == NULL || cpy == NULL)
		return ;
	ft_memcpy(cpy, c, sizeof(t_rgba));
}
