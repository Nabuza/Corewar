/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 15:25:10 by khabbar           #+#    #+#             */
/*   Updated: 2017/11/03 15:36:16 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		ft_print_footer(t_window *win, t_settings *sets)
{
	mvwprintw(win->info, ++(win->y), (win->x = 3), "Cycle to die: %d",
	sets->cycle_to_die);
	mvwprintw(win->info, (win->y), (win->x = 30),
	"(%d remaining)", sets->cycle_to_die - (sets->cycle - sets->start_period));
	win->y++;
	mvwprintw(win->info, ++(win->y), (win->x = 3), "Cycle delta: %d",
	CYCLE_DELTA);
	win->y++;
	mvwprintw(win->info, ++(win->y), (win->x = 3), "Nbr live: %d", NBR_LIVE);
	mvwprintw(win->info, (win->y), (win->x = 30),
	"(%d done)", sets->total_lives);
	win->y++;
	mvwprintw(win->info, ++(win->y), (win->x = 3), "Max check: %d", MAX_CHECKS);
	mvwprintw(win->info, (win->y), (win->x = 30), "(%d done)", sets->checks);
}

static void		ft_print_players(t_window *win, t_settings *sets)
{
	unsigned int	i;

	i = 0xffffffff;
	while (++i < sets->nb_champs)
	{
		mvwprintw(win->info, (win->y)++, (win->x = 3), "Player -%d: ", i + 1);
		wattron(win->info, COLOR_PAIR(i + 1));
		mvwprintw(win->info, win->y - 1, (win->x = 14), "%s",
		sets->champs[i].prog_name);
		if (((sets->status >> (3 * 8)) & 0xff) == i + 1)
			mvwprintw(win->info, win->y, (win->x = 3), "%C ", L'♡');
		wattron(win->info, COLOR_PAIR(5));
		mvwprintw(win->info, (win->y)++, (win->x = 7), "Last live: %d",
		sets->lives[i].last_live);
		mvwprintw(win->info, (win->y)++, (win->x = 7),
		"Live in current period: %d", sets->lives[i].current_period);
		win->y++;
	}
}

static void		ft_print_header(t_window *win, t_settings *sets)
{
	mvwprintw(win->info, 1, (win->x = 3), " ** %s **",
	sets->status & PAUSE ? "PAUSED" : "RUNNING");
	mvwprintw(win->info, (win->y = 4), win->x, "Cycles/second limit : %d",
	sets->speed_limit);
	mvwprintw(win->info, (win->y = 7), win->x, "Cycle: %d", sets->cycle);
	mvwprintw(win->info, (win->y = 10), win->x, "Processes: %d",
	sets->processes);
	if (sets->deaths_proc)
		mvwprintw(win->info, win->y, (win->x = 27), "(Deceased Processes: %d)",
		sets->deaths_proc);
	(win->y = 12);
}

void			ft_graph_info(t_window *win, t_settings *sets)
{
	unsigned int		i;

	if (!win->info && !(win->info = newwin(66, 57, 1, 196)))
		exit(EXIT_FAILURE);
	i = 0xffffffff;
	box(win->info, 0, 0);
	wattron(win->info, COLOR_PAIR(5));
	ft_print_header(win, sets);
	ft_print_players(win, sets);
	ft_live_breakdown(win, sets, "Live breakdown for current period:", 0);
	ft_live_breakdown(win, sets, "Live breakdown for last period:", 1);
	ft_print_footer(win, sets);
	if (sets->status & GAME_ENDED)
		ft_graph_winner(win, sets);
	wrefresh(win->info);
	delwin(win->info);
	win->info = NULL;
}
