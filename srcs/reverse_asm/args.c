/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 14:49:33 by adenis            #+#    #+#             */
/*   Updated: 2017/11/14 18:49:55 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msa.h"

void		get_char(t_oct **lst, int type)
{
	char	arg;
	char	*s;

	if (!(*lst))
		ft_error("Size error");
	arg = (*lst)->content;
	*lst = (*lst)->next;
	if (type == 1)
		write_output("r", 0, NULL);
	if (type == 2)
		write_output("%", 0, NULL);
	write_output((s = ft_itoa(arg)), 0, ", ");
	s ? ft_strdel(&s) : NULL;
}

void		get_short(t_oct **lst, int size, int type)
{
	short	arg;
	int		offset;
	char	*s;

	if (!size || !(*lst))
		return ;
	offset = 8;
	arg = 0;
	while (size)
	{
		if (!(*lst))
			ft_error("Size error");
		arg = (*lst)->content << offset | arg;
		offset -= 8;
		*lst = (*lst)->next;
		size--;
	}
	if (type == 1)
		write_output("r", 0, NULL);
	if (type == 2)
		write_output("%", 0, NULL);
	write_output((s = ft_itoa(arg)), 0, ", ");
	s ? ft_strdel(&s) : NULL;
}

void		get_int(t_oct **lst, int size, int type)
{
	int		arg;
	int		offset;
	char	*s;

	if (!size || !(*lst))
		return ;
	offset = 8 * (size - 1);
	arg = 0;
	while (size > 0)
	{
		if (!(*lst))
			ft_error("Size error");
		arg = (*lst)->content << offset | arg;
		offset -= 8;
		*lst = (*lst)->next;
		size--;
	}
	if (type == 1)
		write_output("r", 0, NULL);
	if (type == 2)
		write_output("%", 0, NULL);
	write_output((s = ft_itoa(arg)), 0, ", ");
	s ? ft_strdel(&s) : NULL;
}

void		get_arg(t_oct **lst, int size, int type)
{
	if (!(*lst))
		return ;
	if (size == 1)
		get_char(lst, type);
	else if (size == 2)
		get_short(lst, size, type);
	else
		get_int(lst, size, type);
}

void		handle_args(t_oct **lst)
{
	t_oct	*tmp;
	int		size;
	int		a;
	int		i;

	a = 0;
	i = 0;
	if (!*lst || !(*lst)->next)
		ft_error("Size error");
	tmp = *lst;
	*lst = (*lst)->next;
	size = g_op_tab[tmp->content - 1].num_params;
	while (i < size)
	{
		a = g_op_tab[tmp->content - 1].params[i];
		get_arg(lst, noct(a, tmp), get_type(a, tmp));
		i++;
	}
}
