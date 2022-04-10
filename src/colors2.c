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

void	add_colors1(t_rgba *a, t_rgba *b, t_rgba *res)
{
	if (!a || !b || !res)
		return ;
	res->r = (a->r + b->r) / 2;
	res->g = (a->g + b->g) / 2;
	res->b = (a->b + b->b) / 2;
	res->a = (a->a + b->a) / 2;
}

void	add_colors3(t_rgba *a, t_rgba *b, t_rgba *res)
{
	if (!a || !b || !res)
		return ;
	res->r = 255 * (a->r + b->r) / (a->r * b->r + 1);
	res->g = 255 * (a->g + b->g) / (a->r * b->r + 1);
	res->b = 255 * (a->b + b->b) / (a->r * b->r + 1);
	res->a = (a->a + b->a) / 2;
}

void	avg_colors(t_rgba *a, t_rgba *b, t_rgba *res)
{
	if (!a || !b || !res)
		return ;
	res->r = a->r * b->r / 255;
	res->g = a->g * b->g / 255;
	res->b = a->b * b->b / 255;
	res->a = (a->a + b->a) / 2;
}

void	avg_colors2(t_rgba *a, double y1, t_rgba *b, double y2, t_rgba *res)
{
	if (!a || !b || !res)
		return ;
	res->r = (a->r * y1 + b->r * y2) / 2;
	res->g = (a->g * y1 + b->g * y2) / 2;
	res->b = (a->b * y1 + b->b * y2) / 2;
	res->a = (a->a + b->a) / 2;
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
