#include "../mrt.h"

t_mat			*create_mat(int n, int m)
{
	t_mat	*out;
	int		i;

	out = ft_allocate(1, sizeof(t_mat));
	out->n = n;
	out->m = m;
	out->data = ft_allocate(n + 1, sizeof(float *));
	i = 0;
	while (i < n)
		out->data[i++] = ft_allocate(m , sizeof(float));
	out->data[i] = NULL;
	return (out);
}

void	delete_mat(t_mat **m)
{
	int i;

	if (!m || !*m)
		return ;
	i = 0;
	while (i < (*m)->n)
		free((*m)->data[i++]);
	free((*m)->data);
	free(*m);
}

t_mat			*mat_sum(t_mat *a, t_mat *b)
{
	t_mat	*out;
	int		i;
	int		j;

	if (!a || !b)
		return (NULL);
	if (a->n != b->n || a->m != b->m)
		return (NULL);
	out = create_mat(a->n, a->m);
	while (i < a->n)
	{
		j = 0;
		while (j < a->m)
		{
			out->data[i][j] = a->data[i][j] + b->data[i][j];
			j++;
		}
		i++;
	}
	out->data[i] = NULL;
	return (out);
}

t_mat			*mat_diff(t_mat *a, t_mat *b)
{
		t_mat	*out;
	int		i;
	int		j;

	if (!a || !b)
		return (NULL);
	if (a->n != b->n || a->m != b->m)
		return (NULL);
	out = create_mat(a->n, a->m);
	while (i < a->n)
	{
		j = 0;
		while (j < a->m)
		{
			out->data[i][j] = a->data[i][j] - b->data[i][j];
			j++;
		}
		i++;
	}
	out->data[i] = NULL;
	return (out);
}

t_mat			*mat_scal(t_mat *a, float k)
{
	t_mat	*out;
	int		i;
	int		j;

	if (!a)
		return (NULL);
	out = create_mat(a->n, a->m);
	while (i < a->n)
	{
		j = 0;
		while (j < a->m)
		{
			out->data[i][j] = a->data[i][j] * k;
			j++;
		}
		i++;
	}
	out->data[i] = NULL;
	return (out);
}

t_mat			*mat_mult(t_mat *a, t_mat *b)
{
	t_mat	*out;
	int		i;
	int		j;
	int		k;

	if (!a || !b || a->m != b->n)
		return (NULL);

	out = create_mat(a->n, b->m);
	while (i < a->n)
	{
		j = 0;
		while (j < b->m)
		{
			k = 0;
			out->data[i][j] = 0;
			while (k < a->m)
			{
				out->data[i][j] += a->data[i][k] * b->data[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	out->data[i] = NULL;
	return (out);
}

t_vect			*mat_vect(t_mat *a, t_vect *v)
{
	t_vect	*out;
	float	**f;

	if (!a || !v || a->n != 4 || a->m != 4)
		return (NULL);
	out = new_vect(0, 0, 0);
	f = a->data;
	out->x = f[0][0] * v->x + f[0][1] * v->y  + f[0][2] * v->z + f[0][3] * v->w;
	out->y = f[1][0] * v->x + f[1][1] * v->y  + f[1][2] * v->z + f[1][3] * v->w;
	out->z = f[2][0] * v->x + f[2][1] * v->y  + f[2][2] * v->z + f[2][3] * v->w;
	out->w = f[3][0] * v->x + f[3][1] * v->y  + f[3][2] * v->z + f[3][3] * v->w;
	return (out);
}

t_vect		*vect_mat(t_vect *v, t_mat *a)
{
		t_vect	*out;
	float	**f;

	if (!a || !v || a->n != 4 || a->m != 4)
		return (NULL);
	out = new_vect(0, 0, 0);
	f = a->data;
	out->x = f[0][0] * v->x + f[1][0] * v->y  + f[2][0] * v->z + f[3][0] * v->w;
	out->y = f[0][1] * v->x + f[1][1] * v->y  + f[2][1] * v->z + f[3][1] * v->w;
	out->z = f[0][2] * v->x + f[1][2] * v->y  + f[2][2] * v->z + f[3][2] * v->w;
	out->w = f[0][3] * v->x + f[1][3] * v->y  + f[2][3] * v->z + f[3][3] * v->w;
	return (out);
}

t_mat			*indentity(int n)
{
	t_mat	*out;
	int		i;
	int		j;

	if (n < 1)
		return (NULL);
	out = create_mat(n, n);
	while (i < n)
	{
		j = 0;
		while (j < n)
		{
			if (i == j)
				out->data[i][j] = 1;
			else
				out->data[i][j] = 0;
			j++;
		}
		i++;
	}
	out->data[i] = NULL;
	return (out);
}

t_mat			*transpose(t_mat *a)
{
	t_mat	*out;
	int		i;
	int		j;

	if (!a)
		return (NULL);
	out = create_mat(a->n, a->m);
	while (i < a->n)
	{
		j = 0;
		while (j < a->m)
		{
			out->data[i][j] = a->data[j][i];
			j++;
		}
		i++;
	}
	out->data[i] = NULL;
	return (out);
}

t_mat			*sub_mat(t_mat *a, int line, int col)
{
	t_mat	*out;
	int		i;
	int		j;
	int		k;
	int		l;

	if (!a || a->m <2 || a->n < 2)
		return (NULL);
	if (line < 0 || line >= a->n || col < 0 || col >= a->m)
		return (NULL);
	out = create_mat(a->n - 1, a->m - 1);
	i = 0;
	l = 0;
	while (l < a->n - 1)
	{
		if (i == line)
			i++;
		j = 0;
		k = 0;
		while (k < a->m - 1)
		{
			if (j == col)
				j++;
			out->data[l][k] = a->data[i][j];
			j++;
			k++;
		}
		i++;
	}
	return (out);
}

float			det_mat(t_mat *a)
{
	float	det;
	t_mat	*tmp;
	int		s;
	int		i;

	if (!a || a->n != a->m)
		ft_exit("Error : determinant of non square matrix !\n", NULL, 1);
	if (a->n == 2)
	{
		det = a->data[0][0] * a->data[1][1] - a->data[1][0] * a->data[0][1];
		return (det);
	}
	det = 0;
	s = 1;
	while (i < a->n)
	{
		tmp = sub_mat(a, 0, i);
		det += s * det_mat(tmp);
		delete_mat(&tmp);
		s *= -1;
		i++;
	}
	return (det);
}
