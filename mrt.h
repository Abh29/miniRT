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


#define EPSILON   1e-6

typedef struct	s_vect {
	float	x;
	float	y;
	float	z;
	int8_t	w;
}	t_vect;

typedef struct s_mat_nm {
	int32_t n;
	int32_t m;
	float 	**data;
}		t_mat;

typedef struct s_rgba {
	int32_t	r;
	int32_t	g;
	int32_t	b;
	float	a;
}	t_rgba;


typedef struct  s_intrsct {
	t_vect	point;
	t_vect	normal;
	t_rgba	color;
	float	dist;
}	t_intrsct;


typedef struct s_camera {
	t_vect	pov;
	t_vect	normal;
	int16_t	fov;
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


typedef struct  s_canvas {
	float	pixel_w;
	float	height;
	float	width;
	t_vect	**cast_rays;
	t_pixel **pixels;
}	t_canvas;


typedef struct s_thcast {
	int			x;
	int			y;
	int			width;
	int			height;
	pthread_t	th_id;
}		t_thcast;

typedef	struct s_2deg_equ {
	float	a;
	float	b;
	float	c;
	float	delta;
	float	x1;
	float	x2;
}		t_2deg_equ;



/**********tools*************/
void			ft_exit(char *str, char *msg, int err);
void			*ft_allocate(int n, int size);
void			ft_free_split(char ***split);


/*********vecters************/
t_vect			*new_vect(int x, int y, int z);
t_vect			*new_point(int x, int y, int z);
void			init_vect(t_vect *v);
void			init_point(t_vect *v);
int				init_vect_str(t_vect *v, char *str);
int				init_point_str(t_vect *v, char *str);
int				is_vect(t_vect *v);
int				is_point(t_vect *v);
void			write_vect(int x, int y, int z, t_vect *v);
int				vect_sum(t_vect *a, t_vect *b, t_vect *sum);
int				vect_diff(t_vect *a, t_vect *b, t_vect *diff);
int				vect_scalar(t_vect *a, float k, t_vect *prod);
float			vect_dot(t_vect *a, t_vect *b);
t_vect			*vect_cross(t_vect *a, t_vect *b);
void			delete_vect(t_vect **v);
int				vect_lin(t_vect *a, t_vect *b);
float			vect_norm(t_vect *v);
float			distance_ptpt(t_vect *a, t_vect *b);
float			distance_ptln(t_vect *a, t_vect *b, t_vect *normal);
float			distance_ptp(t_vect *a, t_plane	*p);
void			mid_point(t_vect *a, t_vect *b, t_vect *mid);
void			normalize(t_vect *v);
int				nullvect(t_vect *v);
float			vect_len(t_vect *v);
int				dist_cmp(t_vect *a, t_vect *b, t_vect *cntr);
float			prjct_resolution(t_vect *a, t_vect *b);

/**********matrices*****************/
t_mat			*create_mat(int n, int m);
void			delete_mat(t_mat **m);
t_mat			*mat_sum(t_mat *a, t_mat *b);
t_mat			*mat_diff(t_mat *a, t_mat *b);
t_mat			*mat_scal(t_mat *a, float k);
t_mat			*mat_mult(t_mat *a, t_mat *b);
t_vect			*mat_vect(t_mat *a, t_vect *v);
t_vect			*vect_mat(t_vect *v, t_mat *a);
t_mat			*indentity(int n);
t_mat			*transpose(t_mat *a);
t_mat			*sub_mat(t_mat *a, int line, int col);
float			det_mat(t_mat *a);
t_mat			*rev_mat(t_mat *a);

/**********colors*******************/

t_rgba			*new_black();
t_rgba			*new_white();
t_rgba			*new_color(int r, int g, int b);
void			init_rgba(t_rgba *c);
int				init_rgba_str(t_rgba *c, char *str);
void			delete_color(t_rgba **c);
void			set_alpha(t_rgba *c, float a);
void			add_colors(t_rgba *a, t_rgba *b, t_rgba *res);
void			diff_colors(t_rgba *a, t_rgba *b, t_rgba *res);
void			mult_colors(t_rgba *a, t_rgba *b, t_rgba *res);
void			alter_color(t_rgba *c, int r, int g, int b);
int				color_to_int(t_rgba *c);
void			int_to_color(int rgb, t_rgba *c);
void			color_cpy(t_rgba *c, t_rgba *dest);

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
t_canvas		*init_canvas(t_camera *c, int H, int W);
void			init_cast_rays(t_canvas *c);
void			init_screen_pixels(t_canvas *c);
void			delete_canvas(t_canvas **sc);
void			init_black_pixel(t_pixel *p, int x, int y);
void			init_camera(t_shape *s, char **spt);
void			init_light(t_shape *s, char **spt);
void			init_ambient(t_shape *s, char **spt);
void			init_sphere(t_shape *s, char **spt);
void			init_plane(t_shape *s, char **spt);
void			init_cylinder(t_shape *s, char **spt);
void			init_hyperbloid(t_shape *s, char **spt);
void			init_quadratic(t_shape *s, char **spt);

/**********parser*************/
t_dlist			*read_file(char *path);
t_shape 		*get_shape(char *line);


/**********intersections*******/
t_intrsct		*new_intersection_point(void);
void			delete_intersection_point(t_intrsct **p);
t_intrsct		*intersection_cpy(t_intrsct *p);
t_intrsct		*intr_shape_vect(t_shape *s, t_vect *v, t_camera *c);
t_intrsct		*intr_light_vect(t_light *s, t_vect *v, t_camera *c);
t_intrsct		*intr_sphere_vect(t_sphere *s, t_vect *v, t_camera *c);
t_intrsct		*intr_plane_vect(t_plane *s, t_vect *v, t_camera *c);
t_intrsct		*intr_cylinder_vect(t_cylinder *s, t_vect *v, t_camera *c);
t_intrsct		*intr_hyperbloid_vect(t_hyperbloid *s, t_vect *v, t_camera *c);
t_intrsct		*intr_quadric_vect(t_quadric *s, t_vect *v, t_camera *c);


/**********transformations*******/
t_mat			*translation_matrix(float x, float y, float z);
t_mat			*scaling_matrix(float x, float y, float z);
t_mat			*rotation_x(float deg);
t_mat			*rotation_y(float deg);
t_mat			*rotation_z(float deg);
t_mat			*shearing(float prp[6]);
t_mat			*rotation_matrix(void);


/*********calculation********/


/**********printers**********/
void			print_vect(t_vect *v);
void			print_mat(t_mat *m);
void			scan_mat(t_mat *m);
void			scan_vect(t_vect *v);
void			print_shape(t_shape *s);

#endif
