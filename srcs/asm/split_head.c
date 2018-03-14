/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_head.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaloul <nagaloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 16:43:00 by nagaloul          #+#    #+#             */
/*   Updated: 2017/11/21 11:17:59 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

static void	ft_header(t_token **tok, t_list **head, int *i)
{
	if ((*head) && ft_countchar((*head)->content, '"') >= 2)
		ft_medium(tok, (*head)->content, i);
	if ((*head) && ft_countchar((*head)->content, '"') == 1)
	{
		ft_hard(tok, head, i);
		if (*head)
			ft_naco2(tok, (*head)->content, i);
	}
}

void		split_head(t_token **tok, t_list **head, int *i)
{
	ft_header(tok, head, i);
}
