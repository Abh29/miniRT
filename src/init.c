#include "../mrt.h"

void	set_camera_up(t_camera *c)
{
	t_vect	v;

	if (c == NULL)
		return;
	v = new_vect(1, 1, 1);
	if (vect_lin(&v, &c->normal))
		write_vect(0, 1, 0, &v);
	c->right = vect_cross(&c->normal, &v);
	c->up = vect_cross(&c->right, &c->normal);
	c->right = vect_cross(&c->normal, &c->up);
	normalize(&c->up);
	normalize(&c->right);
}

t_canvas		*init_canvas(t_camera *c, int H, int W)
{
	t_canvas	*out;
	int			i;

	if (c == NULL || H < 1 || W < 1)
		return (NULL);
	set_camera_up(c);
	write_vect(0,0,1, &c->up);
	write_vect(0,1,0, &c->right);
	out = ft_allocate(1, sizeof(t_canvas));
	out->pixel_w = (2 * tan(c->fov *  M_PI / 360)) / H;
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
	init_cast_rays(out, c);
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

void	init_cast_rays(t_canvas *cnv, t_camera *c)
{
	t_vect v;
	t_vect v2;

	for (int i = 0; i < cnv->height; i++)
	{
		for (int j = 0; j < cnv->width; j++)
		{
			vect_scalar(&c->right, (i - cnv->height / 2) * cnv->pixel_w, &v);
			vect_scalar(&c->up, (j - cnv->width / 2) * cnv->pixel_w, &v2);
			vect_sum(&v, &v2, &cnv->cast_rays[i][j]);
			vect_sum(&c->normal, &cnv->cast_rays[i][j], &cnv->cast_rays[i][j]);
			normalize(&cnv->cast_rays[i][j]);
		}
	}
}

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
		i++;
	}
}

void	init_black_pixel(t_pixel *p, int x, int y)
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




