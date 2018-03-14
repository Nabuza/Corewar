/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 14:50:30 by adenis            #+#    #+#             */
/*   Updated: 2017/11/10 17:08:14 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msa.h"

t_oct		*jump(t_oct *lst, int n)
{
	if (!lst || n <= 0)
		return (lst);
	while (n)
	{
		lst = lst->next;
		n--;
	}
	return (lst);
}

int			noct(int opc, t_oct *lst)
{
	if (!lst)
		ft_error("error");
	if (opc == REG_CODE)
		return (T_REG);
	if (opc == DIR_CODE)
	{
		if (lst->content > 0 && lst->content < 17
			&& g_op_tab[lst->content - 1].short_dir)
			return (T_DIR);
		return (T_DIR * 2);
	}
	if (opc == IND_CODE)
		return (T_IND / 2);
	return (0);
}

int			get_type(int opc, t_oct *lst)
{
	if (!lst)
		ft_error("error");
	if (opc == REG_CODE)
		return (1);
	if (opc == DIR_CODE)
		return (2);
	if (opc == IND_CODE)
		return (3);
	return (0);
}

void		print_cor(t_oct *tmp, t_oct *lst)
{
	char	*s;

	write_output("#", 0, NULL);
	while (tmp != lst)
	{
		write_output((s = ft_itoa_base((unsigned char)tmp->content, 16)),
			0, " ");
		s ? free(s) : 0;
		tmp = tmp->next;
	}
	write_output("\n", 0, NULL);
}

void		lst_val(t_oct *lst)
{
	int		i;

	i = 1;
	while (lst)
	{
		lst->val = i;
		i++;
		lst = lst->next;
	}
}
