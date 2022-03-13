/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:46:38 by mehill            #+#    #+#             */
/*   Updated: 2021/10/22 22:47:16 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new)
{
	t_dlist	*save;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	save = *lst;
	while (save->next)
		save = save->next;
	save->next = new;
	new->prev = save;
}
