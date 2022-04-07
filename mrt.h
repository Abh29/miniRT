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
# include <mlx.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>

#define EPSILON   1e-8

#define CAST_SHADOWS	0

typedef struct	s_vect {
	double	x;
	double	y;
	double	z;
	int8_t	w;
}	t_vect;

typedef struct s_rgba {
	int32_t	r;
	int32_t	g;
	int32_t	b;
	int32_t	a;
}	t_rgba;


typedef	struct s_mat_nm{
	int32_t n;
	int32_t m;
	double	**data;
}	t_mat;

typedef struct s_camera {
	t_vect	pov;
	t_vect	normal;
	t_vect	up;
	t_vect	right;
	int16_t	fov;
}	t_camera;


typedef struct s_ambiant {
	double	ratio;
	t_rgba	color;
}	t_ambient;


typedef struct s_phong
{
	t_rgba		ambient;
	t_ambient	diffuse;
	t_ambient	specular;
	double		roughness;
}		t_phong;


typedef struct s_light {
	t_vect	center;
	double	ratio;
	t_rgba	color;
}	t_light;


typedef	enum e_shapes{
	E_CAMERA,
	E_AMBIENT,
	E_LIGHT,
	E_SPHERE,
	E_PLANE,
	E_CYLINDER,
	E_HYPERBLOID,
	E_QUADRATIC
}		t_shape_id;

typedef struct  s_shape {
	t_shape_id	id;
	void		*shape;
}	t_shape;


typedef struct  s_sphere {
	t_vect	center;
	double	diam;
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
	double	diam;
	double	height;
	t_rgba	color;
}	t_cylinder;

typedef struct	s_hyperbloid {
	t_vect	abc;
	double	k;
	t_rgba	color;
}	t_hyperbloid;

typedef struct s_quadric {
	t_vect	xyz;
	t_vect	xx;
	t_vect	yy;
	t_vect	zz;
	double	k;
	t_rgba	color;
}	t_quadric;

typedef	struct	s_illumination {
	t_rgba	light;
	t_rgba	reflection;
	t_rgba	refraction;
	t_rgba	ambient;
}	t_illm;

typedef struct  s_intrsct {
	t_vect	point;
	t_vect	normal;
	t_vect	eye;
	t_vect	reflect;
	t_vect	lightv;
	t_rgba	color;
	double	dist;
	t_shape	s;
	t_phong	phong;
}	t_intrsct;


typedef struct s_pixel // this will be displayed
{
	int		x;
	int		y;
	t_rgba	color;
	t_rgba	reflection;
}	t_pixel;


typedef struct  s_canvas {
	double	pixel_w;
	double	height;
	double	width;
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
	double	a;
	double	b;
	double	c;
	double	delta;
	double	x1;
	double	x2;
}		t_2deg_equ;


typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_mlx;


/**********tools*************/
void			ft_exit(char *str, char *msg, int err);
void			*ft_allocate(int n, int size);
void			ft_free_split(char ***split);


/*********vecters************/
t_vect			new_vect(double x, double y, double z);
t_vect			new_point(double x, double y, double z);
void			init_vect(t_vect *v);
void			init_point(t_vect *v);
int				init_vect_str(t_vect *v, char *str);
int				init_point_str(t_vect *v, char *str);
int				is_vect(t_vect *v);
int				is_point(t_vect *v);
void			vect_cpy(t_vect *src, t_vect *dst);
void			write_vect(double x, double y, double z, t_vect *v);
void			write_point(double x, double y, double z, t_vect *p);
int				vect_sum(t_vect *a, t_vect *b, t_vect *sum);
int				vect_diff(t_vect *a, t_vect *b, t_vect *diff);
int				vect_scalar(t_vect *a, double k, t_vect *prod);
double			vect_dot(t_vect *a, t_vect *b);
t_vect			vect_cross(t_vect *a, t_vect *b);
void			vect_cross2(t_vect *a, t_vect *b, t_vect *out);
void			delete_vect(t_vect **v);
int				vect_lin(t_vect *a, t_vect *b);
double			vect_norm(t_vect *v);
double			distance_ptpt(t_vect *a, t_vect *b);
double			distance_ptln(t_vect *a, t_vect *b, t_vect *normal);
double			distance_ptp(t_vect *a, t_plane	*p);
void			mid_point(t_vect *a, t_vect *b, t_vect *mid);
void			normalize(t_vect *v);
int				nullvect(t_vect *v);
double			vect_len(t_vect *v);
int				dist_cmp(t_vect *a, t_vect *b, t_vect *cntr);
double			prjct_resolution(t_vect *a, t_vect *b);
void			vect_reflect(t_vect *in, t_vect *normal, t_vect *reflect);

/**********matrices*****************/
t_mat			*create_mat(int n, int m);
void			delete_mat(t_mat **m);
t_mat			*mat_sum(t_mat *a, t_mat *b);
t_mat			*mat_diff(t_mat *a, t_mat *b);
t_mat			*mat_scal(t_mat *a, double k);
t_mat			*mat_mult(t_mat *a, t_mat *b);
t_vect			mat_vect(t_mat *a, t_vect *v);
t_vect			vect_mat(t_vect *v, t_mat *a);
t_mat			*indentity(int n);
t_mat			*transpose(t_mat *a);
t_mat			*sub_mat(t_mat *a, int line, int col);
double			det_mat(t_mat *a);
t_mat			*rev_mat(t_mat *a);

/**********colors*******************/

t_rgba			*new_black();
t_rgba			*new_white();
t_rgba			*new_color(int r, int g, int b);
void			init_rgba(t_rgba *c);
int				init_rgba_str(t_rgba *c, char *str);
void			delete_color(t_rgba **c);
void			set_alpha(t_rgba *c, double a);
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
void			delete_world_objects(t_dlist **obj);

/*********camera*************/
void			set_up_vect(t_camera *c);

/*********init***************/
t_canvas		*init_canvas(t_camera *c, int H, int W);
void			init_cast_rays(t_canvas *cnv, t_camera *c);
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
t_mat			*translation_matrix(double x, double y, double z);
t_mat			*scaling_matrix(double x, double y, double z);
t_mat			*rotation_x(double deg);
t_mat			*rotation_y(double deg);
t_mat			*rotation_z(double deg);
t_mat			*shearing(double prp[6]);
t_mat			*rotation_matrix(void);


/*********casting********/
void	cast_rays(t_canvas *cnv, t_dlist *lst, t_camera *c);
void	get_intersection_info(t_intrsct *p, t_vect *v, t_camera *c);
void	ft_shade(t_intrsct *p, t_dlist *light, t_dlist *obj);

/**********printers**********/
void			print_vect(t_vect *v);
void			print_mat(t_mat *m);
void			scan_mat(t_mat *m);
void			scan_vect(t_vect *v);
void			print_shape(t_shape *s);


/***********display*************/
void	ft_put_pixel(t_mlx *img, int x, int y, int color);

#endif
