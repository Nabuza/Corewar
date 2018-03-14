/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_ctd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 15:14:48 by nolivier          #+#    #+#             */
/*   Updated: 2017/09/25 13:06:09 by nolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			ft_print_death(t_settings *sets, t_process *process)
{
	if (!((sets->options & VERBOSITY) && (sets->options & DEATHS)))
		return ;
	ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
		process->num, sets->cycle - process->last_live, sets->cycle_to_die);
}

static void			ft_reset_process(t_settings *sets, t_process **begin)
{
	t_process		*process;
	t_process		*previous;
	t_process		*tmp;

	process = *begin;
	while (process)
	{
		tmp = process->next;
		if (!(process->status & LIVE))
		{
			(process == *begin) ? (*begin = process->next) :
				(previous->next = process->next);
			ft_print_death(sets, process);
			sets->deaths_proc++;
			sets->processes--;
			free(process);
		}
		else
		{
			process->status &= ~LIVE;
			previous = process;
		}
		process = tmp;
	}
	ft_graph_audio(sets);
}

void				ft_check_ctd(t_settings *sets, t_process **process)
{
	unsigned int		i;

	if (((sets->cycle - sets->start_period) >= sets->cycle_to_die) ||
		sets->cycle_to_die > CYCLE_TO_DIE)
	{
		sets->deaths_proc = 0;
		ft_reset_process(sets, process);
		if (++sets->checks >= MAX_CHECKS || sets->total_lives >= NBR_LIVE)
		{
			sets->checks = 0;
			sets->cycle_to_die -= CYCLE_DELTA;
			if ((sets->options & VERBOSITY) && (sets->options & CYCLES))
				ft_printf("Cycle to die is now %d\n", sets->cycle_to_die);
		}
		i = 0xffffffff;
		while (++i < sets->nb_champs)
		{
			sets->lives[i].last_period = sets->lives[i].current_period;
			sets->lives[i].current_period = 0;
		}
		sets->start_period = sets->cycle;
		sets->total_lives = 0;
	}
}
