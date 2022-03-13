#ifndef MRT_H
#define MRT_H

# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
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
# include <math.h>


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
	t_vect	center;
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
	t_rgba	color;
}	t_hyperbloid;

typedef struct s_quadric {
	t_vect	xyz;
	t_vect	xx;
	t_vect	yy;
	t_vect	zz;
	float	k;
	t_rgba	color;
}	t_quadric;


typedef struct s_pixel // this will be displayed
{
	int		x;
	int		y;
	t_rgba	color;
	t_rgba	reflection;
}	t_pixel;


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



/**********tools*************/
void			ft_exit(char *str, char *msg, int err);
void			*ft_allocate(int size);
void			ft_free_split(char ***split);


/*********vecters************/
t_vect			*new_vect(int x, int y, int z);
void			write_vect(int x, int y, int z, t_vect *v);
void			vect_sum(t_vect *a, t_vect *b, t_vect *sum);
void			vect_diff(t_vect *a, t_vect *b, t_vect *diff);
void			vect_scalar(t_vect *a, float k, t_vect *prod);
float			vect_dot(t_vect *a, t_vect *b);
void			delete_vect(t_vect **v);
float			vect_norm(t_vect *v);
float			distance_ptpt(t_vect *a, t_vect *b);
float			distance_ptln(t_vect *a, t_vect *b, t_vect *normal);
float			distance_ptp(t_vect *a, t_plane	*p);
void			mid_point(t_vect *a, t_vect *b, t_vect *mid);


/**********create-delete*********/
t_shape			*new_shape(void);
void			delete_shape(t_shape **s);
t_camera		*new_camera(void);
void			delete_camera(t_camera **c);
t_ambient		*new_ambient(void);
void			delete_ambient(t_ambient **a);
t_light			*new_light(void);
void			delete_light(t_light **l);
t_sphere		*new_sphere(void);
void			delete_sphere(t_sphere **sp);
t_plane			*new_plane(void);
void			delete_plane(t_plane **pl);
t_cylinder		*new_cylinder(void);
void			delete_cylinder(t_cylinder **cl);
t_hyperbloid	*new_hyperbloid(void);
void			delete_hyperloid(t_hyperbloid **h);
t_quadric		*new_quadric(void);
void			delete_quadric(t_quadric **q);


/*********init***************/
t_screen		*init_screen(t_camera *c, int H, int W);
void			delete_screen(t_screen **sc);
void			init_vect(t_vect *v);
void			init_rgba(t_rgba *c);

/**********parser*************/
t_list			*read_file(char *path);
t_shape 		*get_shape(char *line);


/**********intersections*******/
t_intrsct		*new_intersection_point(void);
void			delete_intersection_point(t_intrsct **p);


/*********calculation********/





#endif