/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstclear_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:48:13 by mehill            #+#    #+#             */
/*   Updated: 2021/10/22 22:57:25 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstclear(t_dlist **lst, void (*del)(void*))
{
	t_dlist	*p;

	if (*lst == NULL)
		return ;
	while (*lst)
	{
		p = *lst;
		*lst = (*lst)->next;
		del(p->content);
		free(p);
	}
	free(*lst);
}
