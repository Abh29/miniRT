#include "../mrt.h"


void	ft_put_pixel(t_mlx *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

t_vect	map_canvas_to_window(t_canvas *cnv, t_mlx *data, int ipx, int jpx)
{
	t_vect v;

	v.x = ipx * cnv->height / data->height;
	v.y = jpx * cnv->width / data->width;
	return (v);
}

t_vect	map_window_to_canvas(t_canvas *cnv, t_mlx *data, int iw, int jw)
{
	t_vect v;

	v.x = iw * data->height / cnv->height;
	v.y = jw * data->width / cnv->width;
	return (v);
}

void	display_canvas(t_canvas *cnv, t_mlx *mlx)
{
	int		color;
	t_vect	v;

	for (int i = 0; i < mlx->height; i++)
	{
		for (int j = 0; j < mlx->width; j++)
		{
			v = map_canvas_to_window(cnv, mlx, i, j);
			color = color_to_int(&cnv->pixels[(int)v.x][(int)v.y].color);
			ft_put_pixel(mlx, i, j, color);
		}	
	}
}

void lazy_canvas_update(t_mrt *w)
{
	w->update = 1;
	delete_canvas(&w->lazy);
	w->lazy = init_canvas(w->c, 100, 100);
	cast_rays(w->lazy, w->objs, w->c);
	display_canvas(w->lazy, &w->display);
	mlx_put_image_to_window(w->display.mlx, w->display.window, w->display.img, 0, 0);
}

void update_canvas(t_mrt *w)
{
	int size[2];

	if (w->update == 0)
		return ;
	w->update = 0;
	size[0] = w->cnv->height;
	size[1] = w->cnv->width;
	delete_canvas(&w->cnv);
	w->cnv = init_canvas(w->c, size[0], size[1]);
	cast_rays(w->cnv, w->objs, w->c);
	display_canvas(w->cnv, &w->display);
	mlx_put_image_to_window(w->display.mlx, w->display.window, w->display.img, 0, 0);
}

void	init_mlx(t_mlx *display, int H, int W)
{
	if (H < 0 || W < 0)
		ft_exit("Error: wrong display size!\n", NULL, 1);
	display->height = H;
	display->width = W;
	display->mlx = mlx_init();
	display->window = mlx_new_window(display->mlx, display->height, display->width, "miniRT");
	display->img =  mlx_new_image(display->mlx, display->height, display->width);
	display->addr = mlx_get_data_addr(display->img, &display->bpp, &display->line_length, &display->endian);
}
