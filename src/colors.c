/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:58:13 by mehill            #+#    #+#             */
/*   Updated: 2022/04/08 21:58:57 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mrt.h"

t_rgba	*new_black(void)
{
	t_rgba	*out;

	out = ft_allocate(1, sizeof(t_rgba));
	out->r = 0;
	out->g = 0;
	out->a = 0;
	out->a = 1;
	return (out);
}

t_rgba	*new_white(void)
{
	t_rgba	*out;

	out = new_black();
	alter_color(out, 255, 255, 255);
	return (out);
}

t_rgba	*new_color(int r, int g, int b)
{
	t_rgba	*out;

	out = new_black();
	alter_color(out, r, g, b);
	return (out);
}

void	init_rgba(t_rgba *c)
{
	if (!c)
		return ;
	c->a = 0;
	c->g = 0;
	c->b = 0;
	c->a = 1;
}

void	delete_color(t_rgba **c)
{
	if (!c || !*c)
		return ;
	free(*c);
}
