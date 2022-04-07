#include "../mrt.h"

t_vect	new_vect(double x, double y, double z)
{
	t_vect	out;

	write_vect(x, y, z, &out);
	out.w = 0;
	return (out);
}

t_vect	new_point(double x, double y, double z)
{
	t_vect	out;

	out = new_vect(x, y, z);
	out.w = 1;
	return (out);
}

void	init_vect(t_vect *v)
{
	if (v == NULL)
		return ;
	v->x = 0;
	v->y = 0;
	v->z = 0;
	v->w = 0;
}

void	init_point(t_vect *v)
{
	if (v == NULL)
		return ;
	v->x = 0;
	v->y = 0;
	v->z = 0;
	v->w = 1;
}

int		is_point(t_vect *v)
{
	if (!v)
		return (0);
	return (v->w == 1);
}

int		is_vect(t_vect *v)
{
	if (!v)
		return (0);
	return (v->w == 0);
}

void	write_vect(double x, double y, double z, t_vect *v)
{
	if (v == NULL)
		return;
	v->x = x;
	v->y = y;
	v->z = z;
	v->w = 0;
}

void	write_point(double x, double y, double z, t_vect *v)
{
	if (v == NULL)
		return;
	v->x = x;
	v->y = y;
	v->z = z;
	v->w = 1;
}

int	vect_sum(t_vect *a, t_vect *b, t_vect *sum)
{
	if (!a || !b || !sum)
		return (0);
	sum->x = a->x + b->x;
	sum->y = a->y + b->y;
	sum->z = a->z + b->z;
	sum->w = a->w + b->w;
	return (sum->w == 0 || sum->w == 1);
}

int	vect_diff(t_vect *a, t_vect *b, t_vect *diff)
{
	if (!a || !b || !diff)
		return (0);
	diff->x = a->x - b->x;
	diff->y = a->y - b->y;
	diff->z = a->z - b->z;
	diff->w = a->w - b->w;
	return (diff->w == 0 || diff->w == 1);
}

int	vect_scalar(t_vect *a, double k, t_vect *prod)
{
	if (!a || !prod)
		return (0);
	prod->x = a->x * k;
	prod->y = a->y * k;
	prod->z = a->z * k;
	prod->w = a->w * k;
	return (is_vect(prod));
}

double	vect_dot(t_vect *a, t_vect *b)
{
	if (!a || !b)
		return INT_MAX;
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

t_vect	vect_cross(t_vect	*a, t_vect *b)
{
	t_vect out;

	out = new_vect(a->y * b->z - a->z * b->y,
					a->z * b->x - a->x * b->z,
					a->x * b->y - a->y * b->x);
	return (out);
}

void	vect_cross2(t_vect	*a, t_vect *b, t_vect *out)
{
	
	write_vect(a->y * b->z - a->z * b->y,
					a->z * b->x - a->x * b->z,
					a->x * b->y - a->y * b->x, out);
	out->w = 0;
}

void	delete_vect(t_vect **v)
{
	free(*v);
}

double	distance_ptpt(t_vect *a, t_vect *b)
{
	double out;

	if (!a || !b)
		return (INT_MAX);
	out = (b->x - a->x) * (b->x - a->x);
	out += (b->y - a->y) * (b->y - a->y);
	out += (b->z - a->z) * (b->z - a->z);
	return (sqrt(out));
}

double	vect_norm(t_vect *v)
{
	if (v == NULL)
		return (INT_MAX);
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}	

double	distance_ptln(t_vect *a, t_vect *b, t_vect *normal)
{
	t_vect diff;

	if (!a || !b || !normal)
		return (INT_MAX);
	vect_diff(b, a, &diff);
	return (vect_dot(&diff, normal) / vect_norm(normal));
}

double	distance_ptp(t_vect *a, t_plane	*p)
{
	double	out;

	if (!a || !p)
		return (INT_MAX);
	out = p->normal.x * a->x + p->normal.y * a->y + p->normal.z * a->z;
	out += vect_dot(&p->normal, &p->point);
	if (out < 0)
		out *= -1;
	return (out / vect_norm(&p->normal));
}

void	mid_point(t_vect *a, t_vect *b, t_vect *mid)
{
	if (!a || !b || !mid)
		return ;
	mid->x = (a->x + b->x) / 2;
	mid->y = (a->y + b->y) / 2;
	mid->z = (a->z + b->z) / 2;
}


int			init_vect_str(t_vect *v, char *str)
{
	char	**spt;

	if (v == NULL || str == NULL)
		return (0);
	spt = ft_split(str, ',');
	if (!spt || !spt[0] || !spt[1] || !spt[2])
		return (0);
	v->x = ft_atod(spt[0]);
	v->y = ft_atod(spt[1]);
	v->z = ft_atod(spt[2]);
	v->w = 0;
	ft_free_split(&spt);
	return (1);
}


int			init_point_str(t_vect *v, char *str)
{
	if (init_vect_str(v, str) == 0)
		return (0);
	v->w = 1;
	return (1);
}


void	normalize(t_vect *v)
{
	double	d;

	if (v == NULL || nullvect(v) || is_point(v))
		return ;
	d = vect_len(v);
	if (d < EPSILON)
		return ;
	v->x /= d;
	v->y /= d;
	v->z /= d;
}


double	vect_len(t_vect *v)
{
	double	out;

	out = sqrt( v->x * v->x + v->y * v->y + v->z * v->z);
	return (out);
}

int				nullvect(t_vect *v)
{
	if (v == NULL)
		return (1);
	if (fabs(v->x) < EPSILON)
		if (fabs(v->y) < EPSILON)
			if (fabs(v->z) < EPSILON)
				return (1);
	return (0);
}


int	vect_lin(t_vect *a, t_vect *b)
{
	if (a == NULL || b == NULL)
		return (1);
	if (nullvect(a) || nullvect(b))
		return (1);
	if (fabs(vect_dot(a, b) - vect_norm(a) * vect_norm(b)) < EPSILON)
		return (1);
	return (0);
}


int	dist_cmp(t_vect *a, t_vect *b, t_vect *cntr)
{
	if ((!a && !b) || !cntr)
		return (0);
	if (distance_ptpt(cntr, a) < distance_ptpt(cntr, b))
		return (1);
	else
		return (-1);
}

double			prjct_resolution(t_vect *a, t_vect *b)
{
	double	out;

	if (!a || !b)
		return (0);
	if (nullvect(a) || nullvect(b))
		return (0);
	out = vect_dot(a, b) / vect_dot(b, b);
	return (out);
}

void			vect_reflect(t_vect *in, t_vect *normal, t_vect *reflect)
{
	double dot;

	if (!in || ! normal || !reflect)
		return ;
	dot = vect_dot(in, normal);
	reflect->x = in->x - 2 * normal->x * dot;
	reflect->y = in->y - 2 * normal->y * dot;
	reflect->z = in->z - 2 * normal->z * dot;
}

void			vect_cpy(t_vect *src, t_vect *dst)
{
	if (src == NULL || dst == NULL)
		return ;
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
	dst->w = src->w;
}
