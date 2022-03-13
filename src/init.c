#include "../mrt.h"

t_screen		*init_screen(t_camera *c, int H, int W)
{
	t_screen	*out;
	int			i;

	if (c == NULL || H < 1 || W < 1)
		return (NULL);
	out = ft_allocate(1, sizeof(t_screen));
	out->pixel_w = 2 * tanf(c->fov / 2) / W;
	out->width = W;
	out->height = H;
	out->cast_rays = ft_allocate(H + 1, sizeof(t_vect *));
	i = 0;
	while (i < H)
		out->cast_rays[i++] = ft_allocate(W + 1, sizeof(t_vect));
	out->cast_rays[i] = NULL;
}

void			delete_screen(t_screen **sc)
{
	int	i;

	if (sc == NULL || *sc == NULL)
		return ;
	i = 0;
	while (i < (*sc)->height)
		free((*sc)->cast_rays[i++]);	
	free((*sc)->cast_rays);
	free(*sc);
}

void			init_vect(t_vect *v)
{
	if (v == NULL)
		return;
	v->x = 0;
	v->y = 0;
	v->z = 0;
}

void			init_rgba(t_rgba *c)
{
	if (c == NULL)
		return;
	c->r = 0;
	c->g = 0;
	c->b = 0;
	c->a = 1;
}
