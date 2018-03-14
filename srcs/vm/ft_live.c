/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 11:54:14 by nolivier          #+#    #+#             */
/*   Updated: 2017/11/03 15:38:05 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		ft_graph_live(t_process *process, t_settings *sets,
	unsigned int id)
{
	sets->info_mem[process->proc_counter * 3] =
	(sets->info_mem[process->proc_counter * 3] & 0xf) | (((id + 1) << 4) &
	0xf0);
	sets->info_mem[process->proc_counter * 3 + 1] |= (LIVE_TIME & 0x7f);
}

static void		ft_print_live(t_settings *sets, t_process *process,
	unsigned int id)
{
	if ((sets->options & VERBOSITY) && (sets->options & OPERATIONS))
		ft_printf("P%5d | live %d\n", process->num, -(id + 1));
}

static void		ft_print_live_player(t_process *process, t_settings *sets,
	unsigned int id)
{
	if (sets->options & NCURSES)
	{
		ft_graph_live(process, sets, id);
		return ;
	}
	if ((sets->options & VERBOSITY) && (sets->options & LIVES))
		ft_printf("Player %d (%s) is said to be alive\n", id + 1,
		(sets->champs + id)->prog_name);
}

static void		ft_check_id(t_settings *sets, t_process *process)
{
	unsigned int		id;
	int					i;

	id = 0;
	i = 0;
	while (i < DIR_SIZE)
	{
		id |= ((sets->memory[(process->proc_counter + 1 + i) % MEM_SIZE])
		^ 0xff) << ((DIR_SIZE - 1 - i) * 8);
		i++;
	}
	ft_print_live(sets, process, id);
	if (id < sets->nb_champs)
	{
		ft_print_live_player(process, sets, id);
		sets->lives[id].last_live = sets->cycle;
		sets->lives[id].current_period++;
		sets->status = (sets->status & 0x00ffffff) |
			(((id + 1) << (3 * 8)) & 0xff000000);
	}
}

int				ft_live(t_settings *sets, t_process *process, t_process **begin)
{
	if (++process->cycle_count < (g_op_tab + 0)->cycles)
		return (1);
	process->status |= LIVE;
	process->last_live = sets->cycle;
	sets->total_lives++;
	ft_check_id(sets, process);
	ft_pc_move(process, sets, DIR_SIZE + 1);
	ft_graph_process(process, sets);
	return (1);
	(void)begin;
}
