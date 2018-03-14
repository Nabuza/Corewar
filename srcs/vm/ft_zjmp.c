/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 11:58:32 by nolivier          #+#    #+#             */
/*   Updated: 2017/09/28 11:39:26 by nolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		ft_print_zjmp(t_process *process, t_settings *sets,
	char *status)
{
	unsigned int	tmp;
	unsigned int	i;

	if (!((sets->options & VERBOSITY) && (sets->options & OPERATIONS)))
		return ;
	tmp = 0;
	i = 0xffffffff;
	while (++i < 2)
		tmp |= (sets->memory[(process->proc_counter + 1 + i) % MEM_SIZE]
		<< (8 * (1 - i)));
	tmp = !(tmp & 0x8000) ? tmp : -(tmp ^ 0xffff) - 1;
	ft_printf("P%5d | zjmp %d %s\n", process->num, tmp, status);
}

static void		ft_jump(t_settings *sets, t_process *process)
{
	unsigned int	index;
	unsigned int	i;

	index = 0;
	i = 0;
	ft_print_zjmp(process, sets, "OK");
	while (i < 2)
	{
		index |= (sets->memory[process->proc_counter + 1 + i]
			<< ((1 - i) * 8)) & (0xff << ((1 - i) * 8));
		i++;
	}
	if (!(0x8000 & index))
		process->proc_counter = (process->proc_counter + (index
		% IDX_MOD)) % MEM_SIZE;
	else
		process->proc_counter = (process->proc_counter -
		(((index ^ 0xffff) + 1) % IDX_MOD)) % MEM_SIZE;
}

int				ft_zjmp(t_settings *sets, t_process *process, t_process **begin)
{
	if (++process->cycle_count < (g_op_tab + 8)->cycles)
		return (1);
	if (process->status & CARRY)
		ft_jump(sets, process);
	else
	{
		ft_print_zjmp(process, sets, "FAILED");
		ft_print_pc_move(process, sets, 3);
		process->proc_counter = (process->proc_counter + 3) % MEM_SIZE;
	}
	process->cycle_count = 0;
	ft_graph_process(process, sets);
	return (1);
	(void)begin;
}
