/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:59:25 by mehill            #+#    #+#             */
/*   Updated: 2022/04/08 22:00:04 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mrt.h"

void	set_alpha(t_rgba *c, double a)
{
	if (c == NULL)
		return ;
	c->a = a;
}

void	add_colors(t_rgba *a, t_rgba *b, t_rgba *res)
{
	if (!a || !b || !res)
		return ;
	res->r = fmin(a->r * a->a + b->r * a->a, 255);
	res->g = fmin(a->g * a->a + b->g * a->a, 255);
	res->b = fmin(a->b * a->a + b->b * a->a, 255);
	res->a = 1;
}

void	diff_colors(t_rgba *a, t_rgba *b, t_rgba *res)
{
	if (!a || !b || !res)
		return ;
	res->r = a->r * a->a - b->r * a->a;
	res->g = a->g * a->a - b->g * a->a;
	res->b = a->b * a->a - b->b * a->a;
	res->a = 1;
}

void	mult_colors(t_rgba *a, t_rgba *b, t_rgba *res)
{
	if (!a || !b || !res)
		return ;
	res->r = a->r * a->a * b->r * a->a / 255;
	res->g = a->g * a->a * b->g * a->a / 255;
	res->b = a->b * a->a * b->b * a->a / 255;
	res->a = 1;
}

void	alter_color(t_rgba *c, int r, int g, int b)
{
	if (c == NULL)
		return ;
	c->r = fmin(fmax(r, 0), 255);
	c->g = fmin(fmax(g, 0), 255);
	c->b = fmin(fmax(b, 0), 255);
}
