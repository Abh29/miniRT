#include "mrt.h"

void	ft_put_pixel(t_mlx *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	display_canvas(t_canvas *cnv, t_mlx *mlx)
{
	int color;

	for (int i = 0; i < cnv->height; i++)
	{
		for (int j = 0; j < cnv->width; j++)
		{
			color = color_to_int(&cnv->pixels[i][j].color);
			ft_put_pixel(mlx, i, j, color);
		}	
	}
	
}

void	cast_rays(t_canvas *cnv, t_shape *s, t_camera *c)
{
	t_intrsct *itr;

	for (int i = 0; i < cnv->height; i++)
	{
		for (int j = 0; j < cnv->width; j++)
		{
			printf("casting (%.2f ,%.2f ,%.2f)\n", cnv->cast_rays[i][j].x, cnv->cast_rays[i][j].y, cnv->cast_rays[i][j].z);
			itr = intr_shape_vect(s, &cnv->cast_rays[i][j], c);
			if (itr)
			{
				printf("hit %d %d\n", i, j);
				color_cpy(&itr->color, &cnv->pixels[i][j].color);
				delete_intersection_point(&itr);
			}
		}
	}
}

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_dlist	*obj;
	t_camera *c = new_camera();
	t_mlx	data;
	
	
	c->fov = 179;
	write_vect(1, 0, 0, &c->normal);
	write_vect(0, 0, 0, &c->pov);
	c->pov.w = 1;
	c->normal.w = 0;
	t_canvas *cnv = init_canvas(c, 512, 512);
	t_sphere sp;
	
	write_vect(-10, 0, 0, &sp.center);
	sp.center.w = 1;
	sp.diam = 5;
	alter_color(&sp.color, 255, 0, 255);
	(void)sp;

	t_plane *pl = new_plane();
	write_vect(-10, 0, 0, &pl->point);
	write_vect(1, 1, 1, &pl->normal);
	alter_color(&pl->color, 0, 255, 0);
	pl->color.a = 0;
	(void) pl;

	t_cylinder *cy = new_cylinder();
	write_vect(-200, 0, 0, &cy->center);
	write_vect(1, 0, 0, &cy->normal);
	cy->diam = 0.1;
	cy->height = 10;
	alter_color(&cy->color, 0, 0, 255);
	(void)cy;

	t_shape s;
	s.id = ft_strdup("cy");
	s.shape = cy;

	t_vect *v = new_vect(1, 0, 0);
	printf("ïntersect %p\n", intr_shape_vect(&s, v, c));

	printf("init canvas done ! \n");
	getchar();

	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, 1920, 1080, "miniRT");
	data.img =  mlx_new_image(data.mlx, 1920, 1080);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_length, &data.endian);
	cast_rays(cnv, &s, c);
	display_canvas(cnv, &data);
//	getchar();
	printf("now put image \n");
//	getchar();
	mlx_put_image_to_window(data.mlx, data.window, data.img, 0, 0);
	mlx_loop(data.mlx);
	
	obj = read_file("testmap");
	
	(void)cnv;
	(void)c;
	(void)obj;
	(void)s;
	return (0);
}
