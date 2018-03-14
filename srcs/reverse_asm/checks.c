/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:15:13 by adenis            #+#    #+#             */
/*   Updated: 2017/11/14 17:57:07 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msa.h"

int		check_magic(t_oct **lst)
{
	t_oct	*tmp;

	tmp = *lst;
	if (!tmp || tmp->content != (unsigned char)(COREWAR_EXEC_MAGIC >> 24))
		return (0);
	tmp = tmp->next;
	if (!tmp || tmp->content != (unsigned char)(COREWAR_EXEC_MAGIC >> 16))
		return (0);
	tmp = tmp->next;
	if (!tmp || tmp->content != (unsigned char)(COREWAR_EXEC_MAGIC >> 8))
		return (0);
	tmp = tmp->next;
	if (!tmp || tmp->content != (unsigned char)COREWAR_EXEC_MAGIC)
		return (0);
	tmp = tmp->next;
	*lst = tmp;
	return (1);
}

int		lstlen(t_oct *lst)
{
	int		i;
	t_oct	*tmp;

	lst ? 0 : ft_error("Size error");
	tmp = lst;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int		check_len(t_oct *lst)
{
	int		len;

	if (!lst)
		ft_error("error");
	len = PROG_NAME_LENGTH + COMMENT_LENGTH + 12;
	if (lstlen(lst) <= len)
	{
		ft_error("bad header length");
		return (0);
	}
	return (1);
}

t_oct	*input_checks(void)
{
	t_oct	*lst;

	lst = LST;
	if (!check_magic(&lst))
		ft_error("invalid magic number");
	check_len(lst);
	return (lst);
}

t_list	*check_goto(t_list *lst, int val)
{
	t_list	*tmp;

	if (!lst)
		ft_error("Size error");
	if (!val)
		return (NULL);
	tmp = OUT;
	while (tmp && tmp->next)
	{
		if ((int)tmp->next->content_size == val)
		{
			if (ft_strstr(tmp->next->content, "label"))
				return (tmp);
			if (isop(tmp->next->content))
				return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
