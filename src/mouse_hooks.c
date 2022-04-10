#include "../mrt.h"


int	ft_mouse_hook(int key, int x, int y, t_mrt *w)
{
	t_vect v = map_canvas_to_window(w->lazy, &w->display, x, y);
	t_dlist	*p = w->objs;
	t_intrsct *itr = NULL;
	t_intrsct *tmp;
	if (key == 1)
	{
		while (p)
		{
			tmp = intr_shape_vect(p->content, &w->lazy->cast_rays[(int)v.x][(int)v.y], w->c);
			if (tmp && !itr && tmp->dist > EPSILON)
				itr = tmp;
			else if (tmp && itr && tmp->dist < itr->dist && tmp->dist > EPSILON)
			{
				delete_intersection_point(&itr);
				itr = tmp;
			}
			else if (tmp)
				delete_intersection_point(&tmp);
			p = p->next;
		}
		if (itr)
		{
			itr->s->selected = itr->s->selected == 1 ? 0 : 1;
			lazy_canvas_update(w);
			delete_intersection_point(&itr);
		}
	}
	return (0);
}
