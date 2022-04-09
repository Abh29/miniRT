#include "../mrt.h"

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

t_mat *get_camera_to_world_matrix(t_camera *c)
{
	t_mat	*m;

	m = indentity(4);
	m->data[0][0] = c->normal.x;
	m->data[0][1] = c->normal.y;
	m->data[0][2] = c->normal.z;
	m->data[1][0] = c->right.x;
	m->data[1][1] = c->right.y;
	m->data[1][2] = c->right.z;
	m->data[2][0] = c->up.x;
	m->data[2][1] = c->up.y;
	m->data[2][2] = c->up.z;
	return (m);
}

void	rotate_camera_on_y(t_mrt *w, double deg)
{
	t_vect	v;
	t_mat	*ctw;
	t_mat	*rym;

	v = new_vect(1, 0, 0);
	ctw = get_camera_to_world_matrix(w->c);
	rym = rotation_y(deg);
	v = vect_mat(&v, rym);
	v = vect_mat(&v, ctw);
	normalize(&v);
	vect_cpy(&v, &w->c->normal);
	lazy_canvas_update(w);
	delete_mat(&ctw);
	delete_mat(&rym);
}

void	rotate_camera_on_z(t_mrt *w, double deg)
{
	t_vect	v;
	t_mat	*ctw;
	t_mat	*rym;

	v = new_vect(1, 0, 0);
	ctw = get_camera_to_world_matrix(w->c);
	rym = rotation_z(deg);
	v = vect_mat(&v, rym);
	v = vect_mat(&v, ctw);
	normalize(&v);
	vect_cpy(&v, &w->c->normal);
	lazy_canvas_update(w);
	delete_mat(&ctw);
	delete_mat(&rym);
}
