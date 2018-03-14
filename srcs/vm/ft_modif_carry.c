/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modif_carry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 14:42:30 by nolivier          #+#    #+#             */
/*   Updated: 2017/09/28 11:21:15 by nolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			ft_modif_carry_reg(t_process *process, unsigned char *reg,
		int op_code)
{
	unsigned int		i;

	if (g_fct_tab[op_code - 1].modif_carry)
	{
		i = 0;
		while (i < REG_SIZE)
		{
			if (reg[i])
			{
				process->status &= ~CARRY;
				return ;
			}
			i++;
		}
		process->status |= CARRY;
	}
}
