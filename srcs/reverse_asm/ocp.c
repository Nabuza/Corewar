/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:31:49 by adenis            #+#    #+#             */
/*   Updated: 2017/11/09 17:35:30 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msa.h"

void		handle_opc(t_oct **lst, int a1, int a2, int a3)
{
	t_oct	*tmp;

	tmp = *lst;
	if (*lst)
		*lst = (*lst)->next;
	if (*lst)
		*lst = (*lst)->next;
	get_arg(lst, noct(a1, tmp), get_type(a1, tmp));
	get_arg(lst, noct(a2, tmp), get_type(a2, tmp));
	get_arg(lst, noct(a3, tmp), get_type(a3, tmp));
}

void		get_opc(t_oct **lst)
{
	t_oct				*tmp;
	unsigned char		opc;
	int					a1;
	int					a2;
	int					a3;

	if (!(*lst) || !(*lst)->next)
		ft_error("Size error");
	tmp = *lst;
	tmp = tmp->next;
	opc = tmp->content;
	a1 = opc / 64;
	opc = opc % 64;
	a2 = opc / 16;
	opc = opc % 16;
	a3 = opc / 4;
	handle_opc(lst, a1, a2, a3);
}
