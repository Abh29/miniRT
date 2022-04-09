#include "mrt.h"

void transform_all_shapes(t_dlist *objs, t_mat *tr)
{
	t_shape *s;

	while (objs != NULL)
	{
		s = objs->content;
		mat_cpy(tr, s->transform);
		s->updated = 1;
		objs = objs->next;
	}
}

int	ft_key_hook(int key, t_mrt *w)
{
	printf("key %d\n", key);
	if (key == 65307 || key == 53)
	{
		delete_world_objects(&w->objs);
		delete_canvas(&w->cnv);
		delete_canvas(&w->lazy);
		mlx_destroy_image(w->display.mlx, w->display.img);
		mlx_destroy_window(w->display.mlx, w->display.window);
		mlx_destroy_display(w->display.mlx);
		printf("bye!\n");
		exit(0);
	}
	if (key == 'r')
		update_canvas(w);
	if (key == 'l')
		lazy_canvas_update(w);
	if ((key == '+' || key == 65451) && w->c->fov > 1)
	{
		w->c->fov -= 1;
		lazy_canvas_update(w);
	}
	if ((key == '-' || key == 65453) && w->c->fov < 179)
	{
		w->c->fov += 1;
		lazy_canvas_update(w);
	}
	if (key == 65362)
	{
		rotate_camera_on_y(w, -10);
		printf("up\n");
	}
	if (key == 65364)
	{	
		rotate_camera_on_y(w, 10);
		printf("down\n");
	}
	if (key == 65363)
	{
		rotate_camera_on_z(w, -10);
		printf("right\n");
	}
	if (key == 65361)
	{
		rotate_camera_on_z(w, 10);
		printf("left\n");	
	}
	if (key == 'z')
	{
		vect_sum(&w->c->pov, &w->c->up, &w->c->pov);
		lazy_canvas_update(w);
	}
	if (key == 's')
	{
		vect_diff(&w->c->pov, &w->c->up, &w->c->pov);
		lazy_canvas_update(w);
	}
	if (key == 'd')
	{
		vect_sum(&w->c->pov, &w->c->right, &w->c->pov);
		lazy_canvas_update(w);
	}
	if (key == 'q')
	{
		vect_diff(&w->c->pov, &w->c->right, &w->c->pov);
		lazy_canvas_update(w);
	}
	if (key == 'e')
	{
		vect_sum(&w->c->pov, &w->c->normal, &w->c->pov);
		lazy_canvas_update(w);
	}
	if (key == 'a')
	{
		vect_diff(&w->c->pov, &w->c->normal, &w->c->pov);
		lazy_canvas_update(w);
	}

	return (0);
}

int	ft_mouse_hook(int key, int x, int y, t_mrt *w)
{
	t_shape *t;
	printf("x : %d   y : %d   key : %d\n", x, y, key);
	t_vect v = map_canvas_to_window(w->cnv, &w->display, x, y);
	printf("i : %lf, j : %lf\n", v.x, v.y);
	print_color(&w->cnv->pixels[(int)v.x][(int)v.y].color);
	t_dlist	*p = w->objs;
	t_intrsct *itr = NULL;
	t_intrsct *tmp;
	while (p)
	{
		tmp = intr_shape_vect(p->content, &w->cnv->cast_rays[(int)v.x][(int)v.y], w->c);
		if (tmp && !itr && tmp->dist > EPSILON)
		{
			t = p->content;
			itr = tmp;
		}
		else if (tmp && itr && tmp->dist < itr->dist && tmp->dist > EPSILON)
		{
			t = p->content;
			delete_intersection_point(&itr);
			itr = tmp;
		}else if (tmp)
			delete_intersection_point(&tmp);
		p = p->next;
	}
	if (itr)
	{
		t->selected = t->selected == 1 ? 0 : 1;
		printf("t id %d\n", t->id);
		printf("opject intersected is %d   selected %d\n", itr->s.id, itr->s.selected);
		update_canvas(w);
		delete_intersection_point(&itr);
	}
	else
		printf("no object intersected !\n");
	return (0);
}

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_mrt	world;

	world.objs = read_file("testmap");
	printf("obj size : %d\n", ft_dlstsize(world.objs));
	world.c = get_camera(world.objs);
	if (world.c == NULL)
		ft_exit("no camera !\n", NULL, 1);
	
	init_mlx(&world.display, 1000, 1000);
	mlx_key_hook(world.display.window, &ft_key_hook, &world);
	mlx_mouse_hook(world.display.window, &ft_mouse_hook, &world);

	world.cnv = init_canvas(world.c, 500, 500);
	world.lazy = init_canvas(world.c, 100, 100);
	printf("init canvas done ! \n");
	//getchar();
	cast_rays(world.cnv, world.objs, world.c);
	printf("ray casting done !\n");
	display_canvas(world.cnv, &world.display);
	mlx_put_image_to_window(world.display.mlx, world.display.window, world.display.img, 0, 0);
	mlx_loop(world.display.mlx);

	return (0);
}
