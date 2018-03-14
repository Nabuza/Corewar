/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ft.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 16:32:29 by adenis            #+#    #+#             */
/*   Updated: 2017/11/22 14:17:13 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	out_lab(t_output *pop)
{
	if (!pop->name)
		return ;
	pop->size = 0;
	pop->val = 0;
}

void	out_comment(t_output *pop)
{
	if (!pop->name)
		return ;
	if (!g_name)
	{
		g_name = 1;
		pop->type = 7;
	}
	pop->name = ft_strsub(pop->name, 1, ft_strlen(pop->name) - 2);
	return ;
}

void	out_dirlab(t_output *pop)
{
	if (!pop->name)
		return ;
	pop->size = 4;
	if (pop->link && g_op_tab[whichop(pop->link->name)].short_dir)
		pop->size = 2;
	pop->val = 0;
}

void	out_indirlab(t_output *pop)
{
	if (!pop->name)
		return ;
	pop->size = 2;
	pop->val = 0;
}

void	out_dir(t_output *pop)
{
	if (!pop->name)
		return ;
	pop->size = 4;
	if (pop->link && g_op_tab[whichop(pop->link->name)].short_dir)
		pop->size = 2;
	pop->val = ft_atoi(&(pop->name)[1]);
}
