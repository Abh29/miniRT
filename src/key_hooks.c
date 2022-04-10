#include "../mrt.h"

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

int	is_selected(t_dlist *objs)
{
	t_shape	*s;

	while (objs)
	{
		s = objs->content;
		if (s->selected)
			return (1);
		objs = objs->next;
	}
	return (0);
}

void unselect_all(t_dlist *objs)
{
	t_shape	*s;

	while (objs)
	{
		s = objs->content;
		s->selected = 0;
		objs = objs->next;
	}
}

void	display_all(t_dlist *objs)
{
	t_shape	*s;

	while (objs)
	{
		s = objs->content;
		s->hide = 0;
		objs = objs->next;
	}
}

void	hide_selected(t_dlist *objs)
{
	t_shape	*s;

	while (objs)
	{
		s = objs->content;
		if (s->selected)
			s->hide = 1;
		s->selected = 0;
		objs = objs->next;
	}
}

void reflect_selected(t_dlist *obj, double ref)
{
	t_shape *s;

	if (obj == NULL)
		return ;
	while (obj)
	{
		s = obj->content;
		if (s->selected)
			s->rflct = ref;
		obj = obj->next;
	}
}

void alter_color_selected(t_dlist *obj, t_cpttrn ptrn)
{
	t_shape *s;

	if (obj == NULL)
		return ;
	while (obj)
	{
		s = obj->content;
		if (s->selected)
			s->c_pattern = ptrn;
		obj = obj->next;
	}
}

int	ft_key_hook(int key, t_mrt *w)
{
	int selected;

	selected = is_selected(w->objs);
	if (key == 65307 || key == 53)
		exit_mrt(w);
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
	if (key == '*' || key == 65450)
	{
		reflect_selected(w->objs, 0.5);
		lazy_canvas_update(w);
	}
	if (key == '/' || key == 65455)
	{
		reflect_selected(w->objs, 0);
		lazy_canvas_update(w);
	}
	if (key == 65362) //up
		rotate_camera_on_y(w, -10);
	if (key == 65364) //down
		rotate_camera_on_y(w, 10);
	if (key == 65363) //right
		rotate_camera_on_z(w, -10);
	if (key == 65361) //left
		rotate_camera_on_z(w, 10);
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
	if (key == 65436 && selected)//3
	{
		t_mat *tr = scaling_matrix(2, 2, 2);
		transform_selected(w->objs, NULL, tr, NULL);
		lazy_canvas_update(w);
	}
	if (key == 65435 && selected)//1
	{
		t_mat *tr = scaling_matrix(0.5, 0.5, 0.5);
		transform_selected(w->objs, NULL, tr, NULL);
		lazy_canvas_update(w);
	}
	if (key == 65431 && selected) //8
	{
		t_mat *tr = translation_matrix(1, 0, 0);
		transform_selected(w->objs, tr, NULL, NULL);
		lazy_canvas_update(w);
	}
	if (key == 65433 && selected) //2
	{
		t_mat *tr = translation_matrix(-1, 0, 0);
		transform_selected(w->objs, tr, NULL, NULL);
		lazy_canvas_update(w);
	}
	if (key == 65432 && selected) //6
	{
		t_mat *tr = translation_matrix(0, 1, 0);
		transform_selected(w->objs, tr, NULL, NULL);
		lazy_canvas_update(w);
	}
	if (key == 65430 && selected) //4
	{
		t_mat *tr = translation_matrix(0, -1, 0);
		transform_selected(w->objs, tr, NULL, NULL);
		lazy_canvas_update(w);
	}
	if (key == 65434 && selected) //9
	{
		t_mat *tr = translation_matrix(0, 0, 1);
		transform_selected(w->objs, tr, NULL, NULL);
		lazy_canvas_update(w);
	}
	if (key == 65429 && selected) //7
	{
		t_mat *tr = translation_matrix(0, 0, -1);
		transform_selected(w->objs, tr, NULL, NULL);
		lazy_canvas_update(w);
	}
	if (key == 'w' && selected)
	{
		unselect_all(w->objs);
		lazy_canvas_update(w);
	}
	if (key == 'i' && selected)
	{
		t_mat *tr = rotation_x(10);
		transform_selected(w->objs, NULL, NULL, tr);
		lazy_canvas_update(w);
	}
	if (key == 'k' && selected)
	{
		t_mat *tr = rotation_x(-10);
		transform_selected(w->objs, NULL, NULL, tr);
		lazy_canvas_update(w);
	}
	if (key == 'o' && selected)
	{
		t_mat *tr = rotation_y(10);
		transform_selected(w->objs, NULL, NULL, tr);
		lazy_canvas_update(w);
	}
	if (key == 'l' && selected)
	{
		t_mat *tr = rotation_y(-10);
		transform_selected(w->objs, NULL, NULL, tr);
		lazy_canvas_update(w);
	}
		if (key == 'p' && selected)
	{
		t_mat *tr = rotation_z(10);
		transform_selected(w->objs, NULL, NULL, tr);
		lazy_canvas_update(w);
	}
	if (key == 'm' && selected)
	{
		t_mat *tr = rotation_z(-10);
		transform_selected(w->objs, NULL, NULL, tr);
		lazy_canvas_update(w);
	}
	if (key == 'c' && selected)
	{
		alter_color_selected(w->objs, E_CHECKER);
		lazy_canvas_update(w);
	}
	if (key == 'v' && selected)
	{
		alter_color_selected(w->objs, E_NONE);
		lazy_canvas_update(w);
	}
	if (key == 'h' && selected)
	{
		hide_selected(w->objs);
		lazy_canvas_update(w);
	}
	if (key == 'y')
	{
		display_all(w->objs);
		lazy_canvas_update(w);
	}
	return (0);
}
