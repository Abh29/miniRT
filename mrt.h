#ifndef MRT_H
#define MRT_H

# include <math.h>
# include <stdlib.h>
# include <stddef.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <mlx.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>


typedef struct	s_vect {
	float	x;
	float	y;
	float	z;
}	t_vect;


typedef struct s_rgba {
	int8_t	r;
	int8_t	g;
	int8_t	b;
	float	a;
}	t_rgba;


typedef struct  s_intrsct {
	t_vect	point;
	t_vect	normal;
	t_rgba	color;
}	t_intrsct;


typedef struct s_camera {
	t_vect	pov;
	t_vect	normal;
	int8_t	fov;
}	t_camera;


typedef struct s_ambiant {
	float	ratio;
	t_rgba	color;
}	t_ambient;


typedef struct s_light {
	t_vect	pol;
	float	ratio;
	t_rgba	color;
}	t_light;


typedef struct  s_shape {
	char	*id;
	void	*shape;
}	t_shape;


typedef struct  s_sphere {
	t_vect	center;
	float	diam;
	t_rgba	color;
}	t_sphere;

typedef struct	s_plane {
	t_vect	point;
	t_vect	normal;
	t_rgba	color;
}	t_plane;


typedef struct s_cylinder {
	t_vect	center;
	t_vect	normal;
	float	diam;
	float	height;
	t_rgba	color;
}	t_cylinder;

typedef struct	s_hyperbloid {
	t_vect	abc;
	float	k;
}	t_hyperbloid;

typedef struct s_quadric {
	t_vect	xyz;
	t_vect	xx;
	t_vect	yy;
	t_vect	zz;
	float	k;
}	t_quadric;


typedef struct  s_screen {
	float	pixel_w;
	float	height;
	float	width;
	t_vect	**cast_rays;
}	t_screen;


typedef struct s_thcast {
	int			x;
	int			y;
	int			width;
	int			height;
	pthread_t	th_id;
}		t_thcast;





#endif