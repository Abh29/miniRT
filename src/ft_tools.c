/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 22:18:12 by mehill            #+#    #+#             */
/*   Updated: 2022/04/08 22:18:17 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mrt.h"

void	ft_exit(char *str, char *msg, int err)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	if (msg)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	exit(err);
}

void	ft_free_split(char ***split)
{
	void	*p;

	p = (char **)*split;
	if (split == NULL || *split == NULL)
		return ;
	while (**split != NULL)
	{
		free(**split);
		**split = NULL;
		(*split)++;
	}
	*split = NULL;
	free(p);
	p = NULL;
}

void	*ft_allocate(int n, int size)
{
	void	*out;

	if (size < 1 || n < 1)
		return (NULL);
	out = ft_calloc(n, size);
	if (out == NULL)
		ft_exit("Error : coult not allocate memroy !\n", NULL, 1);
	return (out);
}
