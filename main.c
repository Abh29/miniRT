#include "mrt.h"



int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	t_mat *m = create_mat(5, 5);
	scan_mat(m);
	print_mat(m);
	printf("det  = %f\n", det_mat(m));

	printf("hello world \n");
	return (0);
}
