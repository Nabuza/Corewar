/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaloul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 20:21:53 by nagaloul          #+#    #+#             */
/*   Updated: 2017/09/17 11:51:08 by nagaloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	ft_push_back(t_list **begin_list, char *data)
{
	t_list *oue;

	oue = *begin_list;
	if (oue)
	{
		while (oue->next != NULL)
			oue = oue->next;
		oue->next = ft_create_elem(data);
	}
	else
		*begin_list = ft_create_elem(data);
}
