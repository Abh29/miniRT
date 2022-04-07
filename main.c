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


int	ft_hook(int key)
{

	printf("key %d\n", key);
	if (key == 65307)
		exit(0);
	return (0);
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
	
	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, 512, 512, "miniRT");
	data.img =  mlx_new_image(data.mlx, 512, 512);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_length, &data.endian);
	mlx_key_hook(data.window, &ft_hook, NULL);

	printf("init canvas start \n");
//	getchar();
	
	printf("camera : \n");
	print_vect(&c->normal);
	print_vect(&c->up);
	print_vect(&c->right);
	t_canvas *cnv = init_canvas(c, 512, 512);
	printf("init canvas done ! \n");
	//getchar();
	cast_rays(cnv, obj, c);
	printf("ray casting done !\n");
//	getchar();
	display_canvas(cnv, &data);
//	getchar();
	printf("now put image \n");
//	getchar();
	mlx_put_image_to_window(data.mlx, data.window, data.img, 0, 0);
	delete_world_objects(&obj);
	mlx_loop(data.mlx);
	
	
	(void)cnv;
	(void)c;
	(void)obj;
	return (0);
}
