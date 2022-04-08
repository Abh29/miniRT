/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 22:21:01 by mehill            #+#    #+#             */
/*   Updated: 2022/04/08 22:21:13 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mrt.h"

t_mat	*shearing(double prp[6])
{
	t_mat	*out;

	out = indentity(4);
	out->data[0][1] = prp[0];
	out->data[0][2] = prp[1];
	out->data[1][0] = prp[2];
	out->data[1][2] = prp[3];
	out->data[2][0] = prp[4];
	out->data[2][1] = prp[5];
	return (out);
}
