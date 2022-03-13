/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_word_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:43:05 by mehill            #+#    #+#             */
/*   Updated: 2021/12/05 20:43:26 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_replace_word(char *str, char *word, int start, int length)
{
	char	*out;
	char	*head;
	char	*tail;
	char	*tmp;

	if (str == NULL)
		return (NULL);
	if (length < 0)
		length = 0;
	head = ft_substr(str, 0, start);
	tail = ft_substr(str, start + length, ft_strlen(str));
	if (word == NULL)
		word = "";
	if (head == NULL)
		head = ft_strdup("");
	tmp = ft_strjoin(head, word);
	if (tail == NULL)
		tail = ft_strdup("");
	out = ft_strjoin(tmp, tail);
	free(head);
	free(tail);
	free(tmp);
	return (out);
}
