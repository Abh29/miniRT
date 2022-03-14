#include "../mrt.h"

t_dlist	*read_file(char *path)
{
	int 	fd;
	t_dlist	*out;
	char	*line;
	t_shape *p;

	if (path == NULL)
		ft_exit("Error : no file_path supplied !\n", NULL, 1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_exit("Error : coult not open", path, 1);
	out = NULL;
	line = get_next_line(fd);
	while (line)
	{
		p = get_shape(line);
		if (p == NULL)
			continue ;
		ft_dlstadd_back(&out, ft_dlstnew(p));
		free(line);
		line = get_next_line(fd);
	}
	return (out);
}



t_shape 		*get_shape(char *line)
{
	t_shape	*out;
	char	**spt;

	if (line == NULL || *line == '\n')
		return (NULL);
	spt = ft_split(line, ' ');
	if (!spt)
		return (NULL);
	out = new_shape();
	if (ft_strcmp(spt[0], "L") == 0)
		init_light(out, spt);
	else if (ft_strcmp(spt[0], "C") == 0)
		init_camera(out, spt);
	else if (ft_strcmp(spt[0], "A") == 0)
		init_ambient(out, spt);
	else if (ft_strcmp(spt[0], "sp") == 0)
		init_sphere(out, spt);
	else if (ft_strcmp(spt[0], "pl") == 0)
		init_plane(out, spt);
	else if (ft_strcmp(spt[0], "cy") == 0)
		init_cylinder(out, spt);
	else if (ft_strcmp(spt[0], "hy") == 0)
		init_hyperbloid(out, spt);
	else if (ft_strcmp(spt[0], "qu") == 0)
		init_quadratic(out, spt);
	else
	{
		ft_free_split(&spt);
		return (NULL);
	}
	ft_free_split(&spt);
	return (out);
}

void			init_camera(t_shape *s, char **spt)
{
	t_camera *c;

	if (!s || !spt || !spt[0] || !spt[1] || !spt[2] || !spt[3])
		ft_exit("Error : not enough info for ", "Camera !", 1);
	s->id = ft_strdup(spt[0]);
	c = ft_allocate(1, sizeof(t_camera));
	if (init_point_str(&c->pov, spt[1]) == 0)
		ft_exit("Error : ill formed point ", "Camera pov !", 1);
	if (init_vect_str(&c->normal, spt[2]) == 0)
		ft_exit("Error : ill formed vector ", "Camera normal !", 1);
	c->fov = ft_atoi(spt[3]);
	if (c->fov < 0 || c->fov > 180)
		ft_exit("Error : ill formed value ", "Camera fov !", 1);
	s->shape = c;	
}

void			init_light(t_shape *s, char **spt)
{
	t_light *l;

	if (!s || !spt || !spt[0] || !spt[1] || !spt[2] || !spt[3])
		ft_exit("Error : not enough info for ", "Light !", 1);
	s->id = ft_strdup(spt[0]);
	l = new_light();
	if (init_point_str(&l->center, spt[1]) == 0)
		ft_exit("Error : ill formed point ", "Light pos !", 1);
	l->ratio = ft_atod(spt[2]);
	if (l->ratio < 0 || l->ratio > 1)
		ft_exit("Error : ill formed value ", "Light ratio !", 1);
	if (init_rgba_str(&l->color, spt[3]) == 0)
		ft_exit("Error : ill formed color ", "Light !", 1);
	s->shape = l;
}

void			init_ambient(t_shape *s, char **spt)
{
	if (!s || !spt || !spt[0] || !spt[1] || !spt[2])
		ft_exit("Error : not enough info for ", "Ambient !", 1);
}

void			init_sphere(t_shape *s, char **spt)
{
	t_sphere *l;

	if (!s || !spt || !spt[0] || !spt[1] || !spt[2] || !spt[3])
		ft_exit("Error : not enough info for ", "Sphere !", 1);
	s->id = ft_strdup(spt[0]);
	l = new_sphere();
	if (init_point_str(&l->center, spt[1]) == 0)
		ft_exit("Error : ill formed point ", "Sphere center !", 1);
	l->diam = ft_atod(spt[2]);
	if (l->diam < 0)
		ft_exit("Error : ill formed value ", "Sphere diam !", 1);
	if (init_rgba_str(&l->color, spt[3]) == 0)
		ft_exit("Error : ill formed color ", "Sphere !", 1);
	s->shape = l;
}

void			init_plane(t_shape *s, char **spt)
{
	t_plane	*l;

	if (!s || !spt || !spt[0] || !spt[1] || !spt[2] || !spt[3])
		ft_exit("Error : not enough info for ", "Plane !", 1);
	s->id = ft_strdup(spt[0]);
	l = new_plane();
	if (init_point_str(&l->point, spt[1]) == 0)
		ft_exit("Error : ill formed point ", "Plane !", 1);
	if (init_vect_str(&l->normal, spt[2]) == 0)
		ft_exit("Error : ill formed vector ", "plane normal !", 1);
	if (init_rgba_str(&l->color, spt[3]) == 0)
		ft_exit("Error : ill formed color ", "plane !", 1);
	s->shape = l;
}

void			init_cylinder(t_shape *s, char **spt)
{
	t_cylinder	*l;

	if (!s || !spt || !spt[0] || !spt[1] || !spt[2] || !spt[3] || !spt[4] || !spt[5])
		ft_exit("Error : not enough info for ", "Cylinder !", 1);
	s->id = ft_strdup(spt[0]);
	l = new_cylinder();
	if (init_point_str(&l->center, spt[1]) == 0)
		ft_exit("Error : ill formed point ", "Cylinder !", 1);
	if (init_vect_str(&l->normal, spt[2]) == 0)
		ft_exit("Error : ill formed vector ", "Cylinder normal !", 1);
	l->diam = ft_atod(spt[3]);
	if (l->diam < 0)
		ft_exit("Error : ill formed value ", "Cylinder diam !", 1);
	l->height = ft_atod(spt[4]);
	if (l->height < 0)
		ft_exit("Error : ill formed value ", "Cylinder height !", 1);
	if (init_rgba_str(&l->color, spt[5]) == 0)
		ft_exit("Error : ill formed color ", "Cylinder !", 1);
	s->shape = l;
}

void			init_hyperbloid(t_shape *s, char **spt)
{
	if (!s || !spt || !spt[0] || !spt[1] || !spt[2])
		ft_exit("Error : not enough info for ", "Hyperbloid !", 1);	
	 (void)s;
	 (void)spt;
}

void			init_quadratic(t_shape *s, char **spt)
{
	if (!s || !spt || !spt[0] || !spt[1] || !spt[2])
		ft_exit("Error : not enough info for ", "Quadratic !", 1);	
	 (void)s;
	 (void)spt;
}
