#include "../mrt.h"

t_mat			*translation_matrix(double x, double y, double z)
{
	t_mat *out;

	out = indentity(4);
	out->data[0][3] = x;
	out->data[1][3] = y;
	out->data[2][3] = z;
	return (out);
}

t_mat			*scaling_matrix(double x, double y, double z)
{
	t_mat *out;

	out = indentity(4);
	out->data[0][0] = x;
	out->data[1][1] = y;
	out->data[2][2] = z;
	return (out);
}

t_mat			*rotation_x(double deg)
{
	double	rad;
	t_mat	*out;

	rad = deg * M_PI / 180;
	out = indentity(4);
	out->data[1][1] = cos(rad);
	out->data[2][1] = sin(rad);
	out->data[1][2] = -sin(rad);
	out->data[2][2] = cos(rad);
	return (out);
}

t_mat			*rotation_y(double deg)
{
	double	rad;
	t_mat	*out;

	rad = deg * M_PI / 180;
	out = indentity(4);
	out->data[0][0] = cos(rad);
	out->data[0][2] = sin(rad);
	out->data[2][0] = -sin(rad);
	out->data[2][2] = cos(rad);
	return (out);
}

t_mat			*rotation_z(double deg)
{
	double	rad;
	t_mat	*out;

	rad = deg * M_PI / 180;
	out = indentity(4);
	out->data[0][0] = cos(rad);
	out->data[0][1] = -sin(rad);
	out->data[1][0] = sin(rad);
	out->data[1][1] = cos(rad);
	return (out);
}

t_mat			*shearing(double prp[6])
{
	t_mat	*out;

	out = indentity(4);
	out->data[0][1] = prp[0];
	out->data[0][2] = prp[1];
	out->data[1][0] = prp[2];
	out->data[1][2] = prp[3];
	out->data[2][0] = prp[4];
	out->data[2][1] = prp[5];
	return (out);
}
