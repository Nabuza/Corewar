/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_kitty_run.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 15:14:48 by nolivier          #+#    #+#             */
/*   Updated: 2017/11/03 15:41:40 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		ft_set_info_mem(t_settings *sets, t_process *process, int mode)
{
	if (!(sets->options & NCURSES))
		return ;
	if (!mode)
		sets->info_mem[3 * process->proc_counter + 1] |= 0x80;
	else
		sets->info_mem[3 * process->proc_counter + 2] |= 0x80;
}

static int		ft_run_one_turn(t_settings *sets, t_process **begin)
{
	t_process		*process;
	unsigned char	op;

	process = *begin;
	while (process)
	{
		if (!process->cycle_count)
		{
			process->status = (process->status & 0xff00ffff) |
			((sets->memory[process->proc_counter] << (2 * 8)) & 0x00ff0000);
		}
		if ((op = (process->status >> (2 * 8)) & 0xff) >= 1 && op <= 16)
		{
			g_fct_tab[op - 1].ptr(sets, process, begin);
			ft_set_info_mem(sets, process, 1);
		}
		else
		{
			process->proc_counter = (process->proc_counter + 1) % MEM_SIZE;
			process->cycle_count = 0;
			ft_set_info_mem(sets, process, 0);
		}
		process = process->next;
	}
	return (1);
}

static void		ft_check_dump(t_settings *sets, t_process **process,
	SCREEN **scr)
{
	t_process		*tmp;

	if (!(sets->status & GAME_ENDED))
	{
		if ((sets->options & MEMORY_DUMP) &&
			sets->cycle >= (unsigned int)sets->memory_cycles)
		{
			ft_dump_memory(sets->memory, MEM_SIZE);
			sets->status |= (GAME_ENDED | GAME_CANCELED);
			while ((*process))
			{
				tmp = (*process);
				(*process) = (*process)->next;
				free(tmp);
			}
			*process = NULL;
		}
		else if ((sets->options & REPEAT_DUMP) && (sets->cycle == 1 ||
		sets->cycle - sets->last_dump >= (unsigned int)sets->repeat_cycles))
		{
			sets->last_dump = sets->cycle;
			ft_press_to_dump(sets, scr);
		}
	}
}

static void		ft_print_cycle(t_settings *sets)
{
	if ((!((sets->options & VERBOSITY) && (sets->options & CYCLES))))
		return ;
	ft_printf("It is now cycle %d\n", sets->cycle);
}

int				ft_run_kitty_run(t_settings *sets, t_window *win)
{
	t_process		*process;
	SCREEN			*scr;

	scr = NULL;
	if (!(process = ft_init_process(sets)))
		return (0);
	sets->cycle = 0;
	sets->last_dump = 0;
	sets->status |= ((sets->nb_champs) << (3 * 8)) & 0xff000000;
	while (!(sets->status & GAME_ENDED))
	{
		ft_graph(sets, win);
		sets->cycle++;
		ft_print_cycle(sets);
		ft_run_one_turn(sets, &process);
		ft_check_ctd(sets, &process);
		if (!(process))
			(sets->status |= GAME_ENDED);
		ft_check_dump(sets, &process, &scr);
		ft_graph_time(sets);
	}
	ft_print_winner(sets, win);
	ft_unset_graph(sets);
	return (1);
}
