#include "../mrt.h"

t_dlist	*read_file(char *path)
{
	int 	fd;
	t_dlist	*out;
	char	*line;
	t_shape *p;

	if (path == NULL)
		ft_exit("Error : no file_path supplied !\n", NULL, 1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_exit("Error : coult not open", path, 1);
	out = NULL;
	line = get_next_line(fd);
	while (line)
	{
		p = get_shape(line);
		if (p == NULL)
			exit(1);
		ft_dlstadd_back(&out, ft_dlstnew(p));
		free(line);
		line = get_next_line(fd);
	}
	return (out);
}
