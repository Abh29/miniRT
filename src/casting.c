#include "../mrt.h"

t_dlist	*get_lights(t_dlist *lst)
{
	t_dlist *out;
	t_shape *s;

	out = NULL;
	while (lst)
	{
		s = lst->content;
		if (s->id == E_LIGHT)
			ft_dlstadd_back(&out, ft_dlstnew(s));
		lst = lst->next;
	}
	return (out);
}

t_dlist	*get_ambient(t_dlist *lst)
{
	t_dlist *out;
	t_shape *s;

	out = NULL;
	while (lst)
	{
		s = lst->content;
		if (s->id == E_AMBIENT)
			ft_dlstadd_back(&out, ft_dlstnew(s));
		lst = lst->next;
	}
	return (out);
}

void	set_phong_ambient(t_intrsct *p, t_dlist **lst)
{
	t_ambient	*l;
	t_shape		*s;

	if (lst == NULL || *lst == NULL)
		return ;
	s = (*lst)->content;
	if (s == NULL || s->id != E_AMBIENT)
		alter_color(&p->phong.ambient, 0, 0, 0);
	else
	{
		l = s->shape;
		p->phong.ambient.r = p->color.r * l->color.r / 255 * l->ratio;
		p->phong.ambient.g = p->color.g * l->color.g / 255 * l->ratio;
		p->phong.ambient.b = p->color.b * l->color.b / 255 * l->ratio;
	}
	//free(*lst); // free content ?
}

void	cast_rays(t_canvas *cnv, t_dlist *lst, t_camera *c)
{
	t_intrsct	*itr, *tmp;
	t_dlist		*p, *light, *amb;
	
	if (lst == NULL || lst->content == NULL)
		return ;
	light = get_lights(lst);(void)light;
	amb = get_ambient(lst);(void)amb;
	p = lst;
	for (int i = 0; i < cnv->height; i++)
	{
		for (int j = 0; j < cnv->width; j++)
		{
			p = lst;
			itr = NULL;
			while (p)
			{
				tmp = intr_shape_vect(p->content, &cnv->cast_rays[i][j], c);
				if (tmp && !itr && tmp->dist > EPSILON)
					itr = tmp;
				else if (tmp && tmp->dist < itr->dist && tmp->dist > EPSILON)
				{
					delete_intersection_point(&itr);
					itr = tmp;
				}else if (tmp)
					delete_intersection_point(&tmp);
				p = p->next;
			}
			if (itr)
			{
				get_intersection_info(itr, &cnv->cast_rays[i][j], c);
				set_phong_ambient(itr, &amb);
				ft_shade(itr, light, lst);
				color_cpy(&itr->phong.diffuse.color, &cnv->pixels[i][j].color);
				delete_intersection_point(&itr);
			}
		}
	}
}

void	get_intersection_info(t_intrsct *p, t_vect *v, t_camera *c)
{
	t_vect 		tmp;
	t_sphere	*s;

	vect_scalar(v, p->dist, &tmp);
	vect_sum(&c->pov, &tmp, &p->point);
	write_vect(v->x, v->y, v->z, &p->eye);
	normalize(&p->eye);
	if (p->s.id == E_SPHERE)
	{
		s = p->s.shape;
		vect_diff(&p->point, &s->center, &p->normal);
		normalize(&p->normal);
		vect_reflect(&p->eye, &p->normal, &p->reflect);
		color_cpy(&p->color, &((t_sphere *)(p->s.shape))->color);
	}
	else if (p->s.id == E_PLANE)
	{
		vect_scalar(&((t_plane *)p->s.shape)->normal, 1, &p->normal);
		color_cpy(&p->color, &((t_plane *)(p->s.shape))->color);
	}
	// else if (p->s.id == E_CYLINDER)
	// {
	// 	(t_cylinder *)p->s.shape;
	// }
	// else if (p->s.id == E_HYPERBLOID)
	// {
	// 	(t_hyperbloid *)p->s.shape;
	// }
	// else if (p->s.id == E_QUADRATIC)
	// {
	// 	(t_quadric *)p->s.shape;
	// }

}

void	ft_shade(t_intrsct *p, t_dlist *light, t_dlist *obj)
{
	t_camera	c;
	t_light		*l;
	t_intrsct	*itr;
	t_dlist		*tmpo;
	t_intrsct	*tmp;
	double		dot_l_n;
	double		dot_r_e;
	double		factor;	

	while (light)
	{
		l = (t_light *)((t_shape *)light->content)->shape;
		vect_diff(&l->center, &p->point, &c.normal);
		write_point(p->point.x, p->point.y, p->point.z, &c.pov);
		tmpo = obj;(void)tmpo;
		itr = NULL;(void)itr;(void)tmp;
		// while (tmpo)
		// {
		// 		tmp = intr_shape_vect(tmpo->content, &c.normal, &c);
		// 		if (tmp && !itr && tmp->dist > EPSILON)
		// 			itr = tmp;
		// 		else if (tmp && tmp->dist < itr->dist && tmp->dist > EPSILON)
		// 		{
		// 			delete_intersection_point(&itr);
		// 			itr = tmp;
		// 		}else if (tmp)
		// 			delete_intersection_point(&tmp);
		// 		tmpo = tmpo->next;
		// }
		if (itr == NULL)
		{
			dot_l_n = vect_dot(&c.normal, &p->normal); // c normal is the light vect
			if (dot_l_n > EPSILON)
			{
				p->phong.diffuse.color.r += p->color.r * p->phong.diffuse.ratio * dot_l_n;
				p->phong.diffuse.color.g += p->color.g * p->phong.diffuse.ratio * dot_l_n;
				p->phong.diffuse.color.b += p->color.b * p->phong.diffuse.ratio * dot_l_n;
				dot_r_e = vect_dot(&p->reflect, &p->eye);
				if (dot_r_e > 0)
				{
					factor = pow(dot_r_e, p->phong.roughness);
					p->phong.specular.color.r += l->color.r * p->phong.specular.ratio * l->ratio * factor;
					p->phong.specular.color.g += l->color.g * p->phong.specular.ratio * l->ratio * factor;
					p->phong.specular.color.b += l->color.b * p->phong.specular.ratio * l->ratio * factor;
				}
			}
		}
		light = light->next;
	}
}
