/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ft_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 16:34:29 by adenis            #+#    #+#             */
/*   Updated: 2017/10/22 19:04:00 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	out_name(t_output *pop)
{
	pop->type = 8;
	return ;
}

void	out_ncom(t_output *pop)
{
	if (!pop->name)
		return ;
	pop->val = 0;
}

void	out_indir(t_output *pop)
{
	if (!pop->name)
		return ;
	pop->size = 2;
	pop->val = ft_atoi(pop->name);
}

void	out_inst(t_output *pop)
{
	if (!pop->name)
		return ;
	pop->size = 1;
	if (g_op_tab[whichop(pop->name)].coding_param)
		pop->size++;
	pop->val = whichop(pop->name) + 1;
	if (pop->size > 1)
		pop->val = pop->val << 8 | ft_opc(pop);
}

void	out_reg(t_output *pop)
{
	if (!pop->name)
		return ;
	pop->size = 1;
	pop->val = ft_atoi(&(pop->name)[1]);
}
