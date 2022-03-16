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
	out = c->a;
	out = (out << 8) + c->r;
	out = (out << 8) + c->g;
	out = (out << 8) + c->b;
	return (out);
}

void			int_to_color(int rgb, t_rgba *c)
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
