/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstmap_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:53:08 by mehill            #+#    #+#             */
/*   Updated: 2021/10/22 22:57:11 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstmap(t_dlist *lst, void *(*f)(void *), void (*del)(void *))
{
	t_dlist	*tmp;
	t_dlist	*root;

	if (lst == NULL)
		return (NULL);
	while (lst)
	{
		tmp = ft_dlstnew(f(lst->content));
		if (tmp == NULL)
		{
			ft_dlstclear(&root, del);
			return (NULL);
		}
		ft_dlstadd_front(&root, tmp);
		lst = lst->next;
	}
	return (root);
}
