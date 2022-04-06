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

t_camera *get_camera(t_dlist *lst)
{
	t_shape *s;
	
	while (lst)
	{
		s = lst->content;
		if (s->id == E_CAMERA)
			return s->shape;
		lst = lst->next;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_dlist	*obj = NULL;
	t_camera *c;
	t_mlx	data;
	
	
	obj = read_file("testmap");
	printf("obj size : %d\n", ft_dlstsize(obj));
	c = get_camera(obj);
	if (c == NULL)
		ft_exit("no camera !\n", NULL, 1);
	t_canvas *cnv = init_canvas(c, 1000, 1000);

	printf("camera : \n");
	print_vect(&c->normal);
	print_vect(&c->up);
	print_vect(&c->right);
	// t_sphere sp;
	// write_vect(10, 0, 0, &sp.center);
	// sp.center.w = 1;
	// sp.diam = 2;
	// alter_color(&sp.color, 255, 0, 0);
	// (void)sp;

	// t_shape s;
	// s.id = E_SPHERE;
	// s.shape = &sp;

	// t_sphere sp2;
	// write_vect(15, 0, 5, &sp2.center);
	// sp2.center.w = 1;
	// sp2.diam = 2;
	// alter_color(&sp2.color, 0, 0, 255);
	// (void)sp2;

	// t_shape s2;
	// s2.id = E_SPHERE;
	// s2.shape = &sp2;
	// (void)s2;

//	ft_dlstadd_back(&obj, ft_dlstnew(&s));
//	ft_dlstadd_back(&obj, ft_dlstnew(&s2));


	// t_vect v = new_vect(1, 0, 0);
	// printf("ïntersect %p\n", intr_shape_vect(&s, &v, c));

	printf("init canvas done ! \n");
	getchar();

	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, 1000, 1000, "miniRT");
	data.img =  mlx_new_image(data.mlx, 1000, 1000);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_length, &data.endian);
	cast_rays(cnv, obj, c);
	printf("ray casting done !\n");
//	getchar();
	display_canvas(cnv, &data);
//	getchar();
	printf("now put image \n");
//	getchar();
	mlx_put_image_to_window(data.mlx, data.window, data.img, 0, 0);
	mlx_loop(data.mlx);
	
	
	(void)cnv;
	(void)c;
	(void)obj;
	return (0);
}
