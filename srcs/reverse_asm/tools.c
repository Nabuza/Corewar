/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 14:59:45 by adenis            #+#    #+#             */
/*   Updated: 2017/11/23 11:03:25 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msa.h"

void	ft_octadd_end(t_oct *alst, t_oct *new)
{
	while (alst->next)
		alst = alst->next;
	alst->next = new;
}

int		ft_error(char *s)
{
	ft_putendl(s);
	clean();
	exit(0);
	return (0);
}

int		ft_usage(void)
{
	ft_putstr("usage: ./reverse_asm [ input_file ]\n");
	exit(0);
	return (0);
}

t_oct	*get_input(int fd)
{
	char	buffer[2];
	t_oct	*lst;
	t_oct	*tmp;

	lst = NULL;
	buffer[1] = '\0';
	while (read(fd, buffer, 1))
	{
		if (!lst)
		{
			(lst = (t_oct *)ft_lstnew(NULL, 0)) ? 0 : ft_error("error");
			lst->content = buffer[0];
		}
		else
		{
			(tmp = (t_oct *)ft_lstnew(NULL, 0)) ? 0 : ft_error("error");
			tmp->content = buffer[0];
			ft_octadd_end(lst, tmp);
			tmp = tmp->next;
		}
	}
	return (lst);
}

void	get_values(t_oct *lst)
{
	t_oct	*tmp;

	if (!lst)
		ft_error("Size error");
	while (lst)
	{
		if (tmp == lst)
			break ;
		tmp = lst;
		if (lst->content <= 0 || lst->content > 16)
			ft_error("Invalid op");
		write_output(g_op_tab[lst->content - 1].label, lst->val, " ");
		if (g_op_tab[lst->content - 1].coding_param)
			get_opc(&lst);
		else
			handle_args(&lst);
		print_cor(tmp, lst);
	}
}
