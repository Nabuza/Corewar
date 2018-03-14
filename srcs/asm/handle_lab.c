/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_lab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 13:59:43 by adenis            #+#    #+#             */
/*   Updated: 2017/11/04 17:56:50 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

t_output	*get_dirlab(char *s)
{
	t_output	*pop;

	pop = OUT;
	while (pop)
	{
		if (pop->type == 0 && !ft_strcmp(s, pop->name))
			return (pop);
		pop = pop->next;
	}
	return (NULL);
}

int			calc_dirlab(short a, short b)
{
	short	res;

	res = b - a;
	return (res);
}

void		fill_dirlab(void)
{
	t_output	*tmp;

	tmp = OUT;
	while (tmp)
	{
		if ((tmp->type == 3 || tmp->type == 5) && get_dirlab(tmp->name))
		{
			tmp->val = calc_dirlab(tmp->link->pos, get_dirlab(tmp->name)->pos);
		}
		tmp = tmp->next;
	}
}
