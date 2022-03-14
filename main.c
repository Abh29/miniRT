#include "mrt.h"



int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_dlist *l = read_file("testmap");
	t_shape *s;

	printf("size of the list : %d\n", ft_dlstsize(l));

	while (l)
	{
		s = l->content;
		printf("shape : %s\n", s->id);
		l = l->next;
	}
	printf("hello world \n");
	return (0);
}
