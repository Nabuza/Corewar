/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 11:54:32 by nolivier          #+#    #+#             */
/*   Updated: 2017/09/28 11:34:13 by nolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		ft_print_add(t_settings *sets, t_process *process)
{
	if ((sets->options & VERBOSITY) && (sets->options & OPERATIONS))
		ft_printf("P%5d | add r%d r%d r%d\n", process->num,
		sets->memory[process->proc_counter + 2],
		sets->memory[process->proc_counter + 3],
		sets->memory[process->proc_counter + 4]);
}

static void		ft_add_reg(unsigned char **params, t_process *process)
{
	unsigned int	i;
	unsigned int	tmp;

	i = 0;
	tmp = 0;
	while (i < REG_SIZE)
	{
		if (tmp & 0x100)
			tmp = params[0][REG_SIZE - 1 - i] +
			params[1][REG_SIZE - 1 - i] + 1;
		else
			tmp = params[0][REG_SIZE - 1 - i] +
			params[1][REG_SIZE - 1 - i];
		params[2][REG_SIZE - 1 - i] = (unsigned char)tmp;
		i++;
	}
	ft_modif_carry_reg(process, params[2], 4);
}

int				ft_add(t_settings *sets, t_process *process,
	t_process **begin)
{
	unsigned char	ocp;
	unsigned int	counter;
	unsigned char	*params[3];

	if (++process->cycle_count < (g_op_tab + 3)->cycles)
		return (1);
	if (!(ocp = ft_get_ocp(sets, process, &counter, params)))
	{
		ft_pc_move(process, sets, counter);
		return (0);
	}
	ft_print_add(sets, process);
	ft_add_reg(params, process);
	ft_pc_move(process, sets, counter);
	ft_graph_process(process, sets);
	return (1);
	(void)begin;
}
