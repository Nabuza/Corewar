/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 20:21:53 by nagaloul          #+#    #+#             */
/*   Updated: 2017/10/30 13:44:37 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"
#include "op.h"

void	ft_push_token(t_token **begin_list, char *data, int i, int b)
{
	t_token *oue;

	oue = *begin_list;
	if (oue)
	{
		while (oue->next != NULL)
			oue = oue->next;
		oue->next = ft_create_token(data, i, b);
	}
	else
		*begin_list = ft_create_token(data, i, b);
}
