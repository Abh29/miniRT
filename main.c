#include "mrt.h"

void	print_help(void)
{
	ft_putstr_fd("z-s q-f a-e           : move camera\n", 1);
	ft_putstr_fd("8-2 6-4 7-9           : move a selected object\n", 1);
	ft_putstr_fd("r                     : refresh screen\n", 1);
	ft_putstr_fd("* /                   : reflect-unreflect object surface\n", 1);
	ft_putstr_fd("+ -                   : change camera's fov\n", 1);
	ft_putstr_fd("up-down right-left    : rotate the camera\n", 1);
	ft_putstr_fd("1-3                   : scale up-down a selected object\n", 1);
	ft_putstr_fd("w                     : unselect all objects\n", 1);
	ft_putstr_fd("i-k o-l p-m           : rotate a selected object\n", 1);
	ft_putstr_fd("h                     : hide selected objects\n", 1);
	ft_putstr_fd("y                     : display all the objects in the scene\n", 1);
}

int	exit_mrt(t_mrt *w)
{
	delete_world_objects(&w->objs);
	delete_canvas(&w->cnv);
	delete_canvas(&w->lazy);
	mlx_destroy_image(w->display.mlx, w->display.img);
	mlx_destroy_window(w->display.mlx, w->display.window);
	mlx_destroy_display(w->display.mlx);
	ft_putstr_fd("bye!\n", 1);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_mrt	world;

	if (argc != 2)
		ft_exit("Error : wrong number of arguments\n", NULL, 1);
	world.objs = read_file(argv[1]);
	world.c = get_camera(world.objs);
	if (world.c == NULL)
		ft_exit("no camera !\n", NULL, 1);
	init_mlx(&world.display, 1000, 1000);
	mlx_key_hook(world.display.window, &ft_key_hook, &world);
	mlx_mouse_hook(world.display.window, &ft_mouse_hook, &world);
	world.cnv = init_canvas(world.c, 750, 750);
	world.lazy = init_canvas(world.c, 180, 180);
	cast_rays(world.cnv, world.objs, world.c);
	display_canvas(world.cnv, &world.display);
	mlx_put_image_to_window(world.display.mlx, world.display.window, world.display.img, 0, 0);
	//mlx_hook(world.display.mlx, 17, 0, exit_mrt, &world);
	print_help();
	mlx_loop(world.display.mlx);
	return (0);
}
