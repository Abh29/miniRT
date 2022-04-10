/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_shapes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 22:07:47 by mehill            #+#    #+#             */
/*   Updated: 2022/04/08 22:14:30 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mrt.h"

int	open_file(char *path)
{
	int	fd;

	if (path == NULL)
		ft_exit("Error : no file_path supplied !\n", NULL, 1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_exit("Error : coult not open", path, 1);
	return (fd);
}

t_dlist	*read_file(char *path)
{
	t_dlist	*out;
	t_shape	*p;
	int		fd;
	char	*line;

	fd = open_file(path);
	out = NULL;
	line = get_next_line(fd);
	while (line)
	{
		line[ft_strlen(line) - 1] = 0;
		p = get_shape(line);
		if (p)
			ft_dlstadd_back(&out, ft_dlstnew(p));
		else if (out)
			add_shape_info(p, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (out);
}

int	get_shape_helper(char **spt, t_shape *out)
{
	if (ft_strcmp(spt[0], "sp") == 0)
		init_sphere(out, spt);
	else if (ft_strcmp(spt[0], "pl") == 0)
		init_plane(out, spt);
	else if (ft_strcmp(spt[0], "cy") == 0)
		init_cylinder(out, spt);
	else if (ft_strcmp(spt[0], "hy") == 0)
		init_hyperbloid(out, spt);
	else if (ft_strcmp(spt[0], "qu") == 0)
		init_quadratic(out, spt);
	else if (ft_strcmp(spt[0], "co") == 0)
		init_cone(out, spt);
	else
		return (0);
	return (1);
}

t_shape	*get_shape(char *line)
{
	t_shape	*out;
	char	**spt;

	if (line == NULL || *line == 0)
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
	else if (get_shape_helper(spt, out))
		(void)spt;
	else
	{
		free(out);
		ft_free_split(&spt);
		return (NULL);
	}
	ft_free_split(&spt);
	out->rflct = 0;
	return (out);
}

void	init_camera(t_shape *s, char **spt)
{
	t_camera	*c;

	if (!s || !spt || !spt[0] || !spt[1] || !spt[2] || !spt[3])
		ft_exit("Error : not enough info for ", "Camera !", 1);
	s->id = E_CAMERA;
	c = ft_allocate(1, sizeof(t_camera));
	if (init_point_str(&c->pov, spt[1]) == 0)
		ft_exit("Error : ill formed point ", "Camera pov !", 1);
	if (init_vect_str(&c->normal, spt[2]) == 0)
		ft_exit("Error : ill formed vector ", "Camera normal !", 1);
	normalize(&c->normal);
	c->fov = ft_atoi(spt[3]);
	if (c->fov < 0 || c->fov > 180)
		ft_exit("Error : ill formed value ", "Camera fov !", 1);
	s->shape = c;
}

void	init_light(t_shape *s, char **spt)
{
	t_light	*l;

	if (!s || !spt || !spt[0] || !spt[1] || !spt[2] || !spt[3])
		ft_exit("Error : not enough info for ", "Light !", 1);
	s->id = E_LIGHT;
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
