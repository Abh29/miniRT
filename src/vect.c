#include "../mrt.h"

t_vect	*new_vect(int x, int y, int z)
{
	t_vect	*out;

	out = malloc(sizeof(t_vect));
	if (out == NULL)
		ft_exit("Error : could not allocate memory !\n", NULL, 1);
	write_vect(x, y, z, &out);
	return (out);
}

void	write_vect(int x, int y, int z, t_vect *v)
{
	if (v == NULL)
		return;
	v->x = x;
	v->y = y;
	v->z = z;
}

void	vect_sum(t_vect *a, t_vect *b, t_vect *sum)
{
	if (!a || !b || !sum)
		return ;
	sum->x = a->x + b->x;
	sum->y = a->y + b->y;
	sum->z = a->z + b->z;
}

void	vect_diff(t_vect *a, t_vect *b, t_vect *diff)
{
	if (!a || !b || !diff)
		return ;
	diff->x = a->x - b->x;
	diff->y = a->y - b->y;
	diff->z = a->z - b->z;
}

void	vect_scalar(t_vect *a, float k, t_vect *prod)
{
	if (!a || !prod)
		return ;
	prod->x = a->x * k;
	prod->y = a->y * k;
	prod->z = a->z * k;
}

float	vect_dot(t_vect *a, t_vect *b)
{
	if (!a || !b)
		return INT_MAX;
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

void	delete_vect(t_vect **v)
{
	free(*v);
}

float	distance_ptpt(t_vect *a, t_vect *b)
{
	float out;

	out = powf(b->x - a->x, 2);
	out += powf(b->y - a->y, 2);
	out += powf(b->z - a->z, 2);
	return (sqrtf(out));
}

float	vect_norm(t_vect *v)
{
	if (v == NULL)
		return (INT_MAX);
	return (sqrtf(v->x * v->x + v->y * v->y + v->z * v->z));
}	

float	distance_ptln(t_vect *a, t_vect *b, t_vect *normal)
{
	t_vect diff;

	if (!a || !b || !normal)
		return (INT_MAX);
	vect_diff(b, a, &diff);
	return (vect_dot(&diff, normal) / vect_norm(normal));
}

float	distance_ptp(t_vect *a, t_plane	*p)
{
	float	out;

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
		return (NULL);
	mid->x = (a->x + b->x) / 2;
	mid->y = (a->y + b->y) / 2;
	mid->z = (a->z + b->z) / 2;
}


