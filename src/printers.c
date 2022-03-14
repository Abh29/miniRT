#include "../mrt.h"
#include <stdio.h>

void			print_vect(t_vect *v)
{
	if (v == NULL)
		printf("(null_vect)\n");
	else
	{
		printf("( %.2f, %.2f, %.2f) ", v->x, v->y, v->z);
		printf("%s\n", v->w == 0 ? "vector" : "point");
	}
}

void			print_mat(t_mat *m)
{
	if (m == NULL)
	{
		printf("(null_matrix)\n");
		return ;
	}
	for (int i = 0; i < m->n; i++)
	{
		for (int j = 0; j < m->m; j++)
		{
			printf(" %.2f |", m->data[i][j]);
		}
		printf("\n");
	}
}

void			scan_mat(t_mat *m)
{
	if (m == NULL)
	{
		printf("(null_matrix)\n");
		return ;
	}
	for (int i = 0; i < m->n; i++)
	{
		for (int j = 0; j < m->m; j++)
		{
			printf("\n%d , %d : ", i, j);
			scanf("%f", &m->data[i][j]);
		}
	}
}

void			scan_vect(t_vect *v)
{
	if (v == NULL)
		printf("(null_vect)\n");
	else
	{
		scanf("%f%f%f", &v->x, &v->y, &v->z);
		scanf("%hhd", &v->w);
		printf("%s", v->w == 0 ? "vector" : "point");
	}
}
