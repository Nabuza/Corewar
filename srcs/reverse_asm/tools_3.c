/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:53:34 by adenis            #+#    #+#             */
/*   Updated: 2017/11/23 11:42:32 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msa.h"

void		del(void *content, size_t size)
{
	size = 0;
	content ? free(content) : 0;
}

void		out_del(t_oct *lst)
{
	if (!lst)
		return ;
	if (lst->next)
		out_del(lst->next);
	lst ? free(lst) : 0;
}

void		lst_del(t_list **lst)
{
	if (*lst)
		return ;
	if ((*lst)->next)
		lst_del(&(*lst)->next);
	del((*lst)->content, (*lst)->content_size);
	*lst ? free(*lst) : 0;
}

void		clean(void)
{
	LST ? out_del(LST) : 0;
	OUT ? lst_del(&OUT) : 0;
	LINE ? ft_strdel(&LINE) : 0;
}
