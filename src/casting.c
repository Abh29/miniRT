#include "../mrt.h"

sem_t count;
int n_count = 0;
typedef struct casting
{
	t_canvas	*cnv;
	t_camera	*c;
	t_dlist		*objs;
	t_dlist		*lights;
	t_dlist		*ambient;
	int			s_w;
	int			e_w;
	int			s_h;
	int			e_h;
}	t_casting_args;


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
		p->phong.ambient.a = 1;
	}
	//free(*lst); // free content ?
}

void	add_global_pattern(t_intrsct *itr, t_canvas *cnv, int i, int j)
{
	t_rgba *c;

	c = new_color(10, 10, 10);
	if ((((int) itr->point.x) % 4) != (((int) itr->point.y) % 4) \
		&& (((int) itr->point.x) % 4) != (((int) itr->point.z) % 4) \
		&& (((int) itr->point.y) % 4) != (((int) itr->point.z) % 4))
		add_colors(c, &cnv->pixels[i][j].color, &cnv->pixels[i][j].color);
	delete_color(&c);
}

void	color_chromaticity(t_rgba *c, t_rgba *dest)
{
	if (c == NULL || dest == NULL)
		return ;
	if (c->r || c->g || c->b)
	{
		dest->r = c->r / (c->r + c->g + c->b) * 255;
		dest->g = c->g / (c->r + c->g + c->b) * 255;
		dest->b = c->b / (c->r + c->g + c->b) * 255;
	}
	else
		alter_color(dest, 0, 0, 0);
}

void	set_pixel_color(t_canvas *cnv, t_intrsct *itr, int i, int j)
{
//	color_cpy(&itr->color, &cnv->pixels[i][j].color);
//	color_chromaticity(&cnv->pixels[i][j].color, &cnv->pixels[i][j].color);
	color_cpy(&itr->phong.ambient, &cnv->pixels[i][j].color);
	add_colors(&itr->phong.diffuse.color, &cnv->pixels[i][j].color, &cnv->pixels[i][j].color);
	add_colors(&itr->phong.specular.color, &cnv->pixels[i][j].color, &cnv->pixels[i][j].color);
	avg_colors2(&itr->phong.reflection, itr->s->rflct, &cnv->pixels[i][j].color, 2 - itr->s->rflct, &cnv->pixels[i][j].color);
//	add_global_pattern(itr, cnv, i, j);
	if (itr->s->selected)
	{
		cnv->pixels[i][j].color.r = cnv->pixels[i][j].color.r / 2 + 120;
		cnv->pixels[i][j].color.g = cnv->pixels[i][j].color.g / 2 + 120;
		cnv->pixels[i][j].color.b = cnv->pixels[i][j].color.b / 2 + 120;
	}
}

void	set_phong_reflection(t_intrsct *p, t_dlist *light, t_dlist *obj, int rec)
{
	t_intrsct *itr = NULL;
	t_intrsct *tmp;
	t_camera	c;
	t_dlist		*os;

	if (rec < 1)
		return ;
	vect_cpy(&p->point, &c.pov);
	vect_cpy(&p->reflect, &c.normal);
	os = obj;
	while (os)
	{
		tmp = intr_shape_vect(os->content, &c.normal, &c);
		if (tmp && !itr && tmp->dist > EPSILON)
			itr = tmp;
		else if (tmp && itr && tmp->dist < itr->dist && tmp->dist > EPSILON)
		{
			delete_intersection_point(&itr);
			itr = tmp;
		}
		else if (tmp)
			delete_intersection_point(&tmp);
		os = os->next;
	}
	if (itr)
	{
		get_intersection_info(itr, &c.normal, &c);
		ft_shade(itr, light, obj);
		set_phong_reflection(itr, light, obj, rec - 1);
		color_cpy(&itr->phong.ambient, &p->phong.reflection);
		add_colors(&itr->phong.diffuse.color, &p->phong.reflection, &p->phong.reflection);
		add_colors(&itr->phong.specular.color, &p->phong.reflection, &p->phong.reflection);
		delete_intersection_point(&itr);
	}
}

void	*cast_one_ray(void	*args)
{
	t_casting_args	*a;
	t_intrsct		*itr;
	t_intrsct		*tmp;
	t_dlist			*p;

	a = (t_casting_args *)args;
	for (int i = a->s_h; i < a->e_h; i++)
	{
		for (int j = a->s_w; j < a->e_w; j++)
		{
			p = a->objs;
			itr = NULL;
			while (p)
			{
				tmp = intr_shape_vect(p->content, &a->cnv->cast_rays[i][j], a->c);
				if (tmp && !itr && tmp->dist > EPSILON)
					itr = tmp;
				else if (tmp && itr && tmp->dist < itr->dist && tmp->dist > EPSILON)
				{
					delete_intersection_point(&itr);
					itr = tmp;
				}else if (tmp)
					delete_intersection_point(&tmp);
				p = p->next;
			}
			if (itr)
			{
				get_intersection_info(itr, &a->cnv->cast_rays[i][j], a->c);
				set_phong_ambient(itr, &a->ambient);
				ft_shade(itr, a->lights, a->objs);
				set_phong_reflection(itr, a->lights, a->objs, REFLECTIONS);
				set_pixel_color(a->cnv, itr, i, j);
				delete_intersection_point(&itr);
			}
		}
	}
	return (NULL);
}

void	alter_color_gradient(t_intrsct *p, t_rgba *c1, t_rgba *c2, int on)
{
	double	px; (void)px;
	(void)c1;
	(void)c2;

	if (on == 1)
		px = p->point.x;
	else if (on == 2)
		px = p->point.y;
	else
		px = p->point.z;
	alter_color(&p->color,
		c1->r + (c2->r - c1->r) * (px - floor(px)),
		c1->r + (c2->r - c1->r) * (px - floor(px)),
		c1->r + (c2->r - c1->r) * (px - floor(px)));
}

void	alter_color_stripe(t_intrsct *p, int mod, double y, int on)
{
	double px;

	if (on == 1)
		px = p->point.x;
	else if (on == 2)
		px = p->point.y;
	else
		px = p->point.z;
	if (((int)px) % mod == 0)
		alter_color(&p->color, p->color.r * y, p->color.g * y, p->color.b * y);
}

void	alter_color_pattern(t_intrsct *p, t_vect *mod, double y)
{
	if ((((int) p->point.x) % (int) mod->x) != (((int) p->point.y) % (int) mod->y) \
		&& (((int) p->point.x) % (int) mod->x) != (((int) p->point.z) % (int) mod->z) \
		&& (((int) p->point.y) % (int) mod->y) != (((int) p->point.z) % (int) mod->z))
			alter_color(&p->color, p->color.r * y, p->color.g * y, p->color.b * y);
}

void	alter_color_rings(t_intrsct *p, int mod, double y, int on)
{
	double px;
	double py;

	if (on == 1)
	{
		px = p->point.x;
		py = p->point.y;
	}
	else if (on == 2)
	{
		px = p->point.y;
		py = p->point.z;
	}
	else
	{
		px = p->point.z;
		py = p->point.x;
	}
	if (((int)sqrt(px * px + py * py)) % mod == 0)
		alter_color(&p->color, p->color.r * y, p->color.g * y, p->color.b * y);
}

void alter_color_checkered(t_intrsct *p, int mod, double y)
{
	if (((int) p->point.x + (int)p->point.y + (int)p->point.z) % mod == 0)
		alter_color(&p->color, p->color.r * y, p->color.g * y, p->color.b * y);
}

void	cast_rays(t_canvas *cnv, t_dlist *lst, t_camera *c)
{
	t_dlist			*light, *amb;
	t_casting_args	*a;
	pthread_t		pid[NTH * NTH];
	
	if (lst == NULL || lst->content == NULL)
		return ;
	light = get_lights(lst);(void)light;
	amb = get_ambient(lst);(void)amb;
	a = ft_allocate(NTH * NTH + 1, sizeof(t_casting_args));
	for (int i = 0; i < NTH; i++)
	{
		for (int j = 0; j < NTH; j++)
		{
			a[i * NTH + j].cnv = cnv;
			a[i * NTH + j].ambient = amb;
			a[i * NTH + j].lights = light;
			a[i * NTH + j].c = c;
			a[i * NTH + j].objs = lst;
			a[i * NTH + j].s_h =  i * cnv->height / NTH;
			a[i * NTH + j].e_h = (i + 1) * cnv->height / NTH;
			a[i * NTH + j].s_w =  j * cnv->width / NTH;
			a[i * NTH + j].e_w = (j + 1) * cnv->width / NTH;
			pthread_create(&pid[i * NTH + j], NULL, cast_one_ray, &a[i * NTH + j]);
		//	if ((i % 2) != (j % 2))
		//	cast_one_ray(&a[i * NTH + j]);
		}
	}
	for (int i = 0; i < NTH * NTH; i++)
		pthread_join(pid[i], NULL);
	free(a);
	ft_dlstclear(&light, NULL);
	ft_dlstclear(&amb, NULL);
}

void	get_intersection_info(t_intrsct *p, t_vect *v, t_camera *c)
{
	t_vect 		tmp;
	t_sphere	*s;

	vect_cpy(v, &p->eye);
	normalize(&p->eye);
	if (p->s->id == E_SPHERE)
	{
		s = p->s->shape;
		vect_scalar(v, p->dist, &tmp);
		vect_sum(&c->pov, &tmp, &p->point);
		vect_diff(&p->point, &s->center, &p->normal);
		normalize(&p->normal);
		if (p->inside)
			vect_scalar(&p->normal, -1, &p->normal);
		color_cpy(&((t_sphere *)(p->s->shape))->color ,&p->color);
		if (p->s->c_pattern != E_NONE) 
			alter_color_rings(p, 2, 0.8, 1);
	}
	else if (p->s->id == E_PLANE)
	{
		vect_scalar(v, p->dist, &tmp);
		vect_sum(&c->pov, &tmp, &p->point);
		vect_cpy(&((t_plane *)p->s->shape)->normal, &p->normal);
		color_cpy(&p->color, &((t_plane *)(p->s->shape))->color);
		if (p->s->c_pattern != E_NONE)
		{
			t_vect cp = new_vect(5, 10, 5);
			alter_color_pattern(p, &cp, 0.8);
		}
		else
			alter_color_checkered(p, 2, 0.8);
	}
	else if (p->s->id == E_CYLINDER)
	{
		t_cylinder *cy = p->s->shape;
		vect_diff(&p->point, &cy->center, &tmp);
		vect_scalar(&cy->normal, vect_dot(&tmp, &cy->normal), &tmp);
		vect_diff(&tmp, &p->point, &p->normal);
		if (p->inside)
			vect_scalar(&p->normal, -1, &p->normal);
		normalize(&p->normal);
		if (p->s->c_pattern != E_NONE)
		{
			alter_color_stripe(p, 3, 0.5, 1);
			alter_color_rings(p, 3, 0.5, 2);
		}
	}
	else if (p->s->id == E_CONE)
	{
		t_cone *cy = p->s->shape;
		color_cpy(&cy->color, &p->color);
		if (point_equ(&cy->center, &p->point))
			vect_cpy(&cy->normal, &p->normal);
		if (p->s->c_pattern != E_NONE)
			alter_color_rings(p, 3, 0.5, 2);
	}
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
	double		ldist;

	while (light)
	{
		l = (t_light *)((t_shape *)light->content)->shape;
		vect_diff(&l->center, &p->point, &c.normal);
		ldist = vect_norm(&c.normal);
		vect_cpy(&p->point, &c.pov);
		vect_scalar(&c.normal, -1, &p->lightv);
		vect_reflect(&p->lightv, &p->normal, &p->reflect);
		normalize(&p->lightv);
		normalize(&p->reflect);
		normalize(&c.normal);
		tmpo = obj;(void)tmpo;
		itr = NULL;(void)itr;(void)tmp;
		while (CAST_SHADOWS && tmpo)
		{
				tmp = intr_shape_vect(tmpo->content, &c.normal, &c);
				if (tmp && !itr && tmp->dist > EPSILON && ldist - tmp->dist > EPSILON)
					itr = tmp;
				else if (tmp && itr && tmp->dist < itr->dist && tmp->dist > EPSILON)
				{
					delete_intersection_point(&itr);
					itr = tmp;
				}else if (tmp)
					delete_intersection_point(&tmp);
				tmpo = tmpo->next;
		}
		if (itr == NULL)
		{
			dot_l_n = vect_dot(&p->lightv, &p->normal);
			if (fabs(dot_l_n) > EPSILON)
			{
				p->phong.diffuse.color.r += p->color.r * p->phong.diffuse.ratio * fabs(dot_l_n) * l->color.r / 255 * l->ratio;
				p->phong.diffuse.color.g += p->color.g * p->phong.diffuse.ratio * fabs(dot_l_n) * l->color.g / 255 * l->ratio;
				p->phong.diffuse.color.b += p->color.b * p->phong.diffuse.ratio * fabs(dot_l_n) * l->color.b / 255 * l->ratio;
				dot_r_e = vect_dot(&p->reflect, &p->eye);
				if (dot_r_e < EPSILON)
				{
					factor = pow(dot_r_e, p->phong.roughness);
					p->phong.specular.color.r += l->color.r * p->phong.specular.ratio * l->ratio * factor;
					p->phong.specular.color.g += l->color.g * p->phong.specular.ratio * l->ratio * factor;
					p->phong.specular.color.b += l->color.b * p->phong.specular.ratio * l->ratio * factor;
				}
			}
		}
		else
			delete_intersection_point(&itr);
		p->phong.ambient.r *= l->color.r / 255 * l->ratio;
		p->phong.ambient.g *= l->color.g / 255 * l->ratio;
		p->phong.ambient.b *= l->color.b / 255 * l->ratio;
		light = light->next;
	}
}
