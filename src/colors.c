#include "../mrt.h"

t_rgba			*new_black()
{
	t_rgba *out;

	out = ft_allocate(1, sizeof(t_rgba));
	out->r = 0;
	out->g = 0;
	out->a = 0;
	out->a = 0;
	return (out);
}

t_rgba			*new_white()
{
	t_rgba	*out;

	out = new_black();
	alter_color(out, 255, 255, 255);
	return (out);
}

t_rgba			*new_color(int r, int g, int b)
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

void			delete_color(t_rgba **c)
{
	if (!c || !*c)
		return ;
	free(*c);
}

void			set_alpha(t_rgba *c, float a)
{
	if (c == NULL)
		return ;
	c->a = a;
}

void			add_colors(t_rgba *a, t_rgba *b, t_rgba *res)
{
	if (!a || !b || !res)
		return ;
	res->r = a->r * a->a + b->r * a->a;
	res->g = a->g * a->a + b->g * a->a;
	res->b = a->b * a->a + b->b * a->a;
	res->a = 1;
}

void			diff_colors(t_rgba *a, t_rgba *b, t_rgba *res)
{
	if (!a || !b || !res)
		return ;
	res->r = a->r * a->a - b->r * a->a;
	res->g = a->g * a->a - b->g * a->a;
	res->b = a->b * a->a - b->b * a->a;
	res->a = 1;
}

void			mult_colors(t_rgba *a, t_rgba *b, t_rgba *res)
{
	if (!a || !b || !res)
		return ;
	res->r = a->r * a->a * b->r * a->a / 255;
	res->g = a->g * a->a * b->g * a->a / 255;
	res->b = a->b * a->a * b->b * a->a / 255;
	res->a = 1;
}

void			alter_color(t_rgba *c, int r, int g, int b)
{
	if (c == NULL)
		return ;
	c->r = r;
	c->g = g;
	c->b = b;
}

int				color_to_int(t_rgba *c)
{
	int	out;

	if (!c)
		return (0);
	out = c->r;
	out = (out << 8) + c->g;
	out = (out << 8) + c->b;
	return (out);
}

void			int_to_color(int rgb, t_rgba *c)
{
	if (!c)
		return ;
	c->r = (rgb >> 16) & 0xFF;
	c->g = (rgb >> 8) & 0xFF;
	c->b = rgb & 0xFF;
}

