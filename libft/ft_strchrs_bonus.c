/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrs_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:42:56 by mehill            #+#    #+#             */
/*   Updated: 2021/12/05 20:42:56 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchrs(char *str, char *set)
{
	if (str == NULL || set == NULL)
		return (NULL);
	while (*str)
	{
		if (ft_strchr(set, *str))
			return (str);
		str++;
	}
	return (NULL);
}
