#include "mrt.h"



int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	t_mat *m = create_mat(4, 4);
	scan_mat(m);
	print_mat(m);
	printf("det  = %f\n", det_mat(m));
	t_mat *r = rev_mat(m);
	print_mat(r);
	printf("det  = %f\n", det_mat(r));
	printf("hello world \n");
	return (0);
}
