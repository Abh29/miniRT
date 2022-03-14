#include "../mrt.h"

t_canvas		*init_canvas(t_camera *c, int H, int W)
{
	t_canvas	*out;
	int			i;

	if (c == NULL || H < 1 || W < 1)
		return (NULL);
	out = ft_allocate(1, sizeof(t_canvas));
	out->pixel_w = 2 * tanf(c->fov / 2) / W;
	out->width = W;
	out->height = H;
	out->cast_rays = ft_allocate(H + 1, sizeof(t_vect *));
	out->pixels = ft_allocate(H + 1, sizeof(t_pixel *));
	i = 0;
	while (i < H)
	{
		out->cast_rays[i] = ft_allocate(W + 1, sizeof(t_vect));
		out->pixels[i++] = ft_allocate(W + 1, sizeof(t_pixel));
	}
	out->cast_rays[i] = NULL;
	out->pixels[i] = NULL;
	init_cast_rays(out);
	init_screen_pixels(out);
	return (out);
}

void			delete_screen(t_canvas **sc)
{
	int	i;

	if (sc == NULL || *sc == NULL)
		return ;
	i = 0;
	while (i < (*sc)->height)
		free((*sc)->cast_rays[i++]);
	i = 0;
	while (i < (*sc)->height)
		free((*sc)->pixels[i++]);
	free((*sc)->cast_rays);
	free((*sc)->pixels);
	free(*sc);
}

void	init_cast_rays(t_canvas *c);

void	init_screen_pixels(t_canvas *c)
{
	int	i;
	int j;

	i = 0;
	while (i < c->height)
	{
		j = 0;
		while (j < c->width)
		{
			init_black_pixel(&c->pixels[i][j], i, j);
			j++;
		}
	}
}

void			init_black_pixel(t_pixel *p, int x, int y)
{
	if (!p)
		return ;
	alter_color(&p->color, 0, 0, 0);
	set_alpha(&p->color, 1);
	alter_color(&p->reflection, 0, 0, 0);
	set_alpha(&p->reflection, 1);
	p->x = x;
	p->y = y;
}

