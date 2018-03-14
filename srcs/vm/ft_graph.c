/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 14:14:15 by khabbar           #+#    #+#             */
/*   Updated: 2017/11/03 15:32:56 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		define_color_pairs(void)
{
	init_color(COLOR_WHITE, 255, 255, 255);
	init_color(COLOR_CYAN, 1000, 1000, 1000);
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_P1, COLOR_BLACK);
	init_pair(11, COLOR_P1, COLOR_WHITE);
	init_pair(2, COLOR_P2, COLOR_BLACK);
	init_pair(12, COLOR_P2, COLOR_WHITE);
	init_pair(3, COLOR_P3, COLOR_BLACK);
	init_pair(13, COLOR_P3, COLOR_WHITE);
	init_pair(4, COLOR_P4, COLOR_BLACK);
	init_pair(14, COLOR_P4, COLOR_WHITE);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
}

static void		init_graph(void)
{
	setlocale(LC_ALL, "");
	initscr();
	if (has_colors() == FALSE || can_change_color() == FALSE)
		exit(ft_dprintf(2, "Your terminal doesn't support colors."));
	start_color();
	define_color_pairs();
	noecho();
	cbreak();
	nodelay(stdscr, TRUE);
	curs_set(0);
}

static void		speed_things_up(t_settings *sets, int ch)
{
	if (ch == 113)
		sets->speed_limit += 10;
	else if (ch == 119)
		sets->speed_limit -= 10;
	else if (ch == 101)
		sets->speed_limit += 1;
	else if (ch == 114)
		sets->speed_limit -= 1;
	else if (ch == 116)
		sets->speed_limit = MAX_SPEED;
	if (sets->speed_limit > 1000)
		sets->speed_limit = 1000;
	else if (sets->speed_limit < 1)
		sets->speed_limit = 1;
	sets->cycle_time = 1000000000 / sets->speed_limit;
}

static int		pause_game(t_settings *sets, t_window *win)
{
	int			ch;

	(void)win;
	if ((ch = getch()) == ERR)
		return (sets->status & PAUSE ? 0 : 1);
	if (ch == 32)
	{
		if (sets->status & START)
			sets->status &= ~START;
		return ((sets->status & PAUSE ? (sets->status &= ~PAUSE) :
		!(sets->status |= PAUSE)));
	}
	else if (ch == 113 || ch == 119 || ch == 101 || ch == 114 || ch == 116)
		speed_things_up(sets, ch);
	return (0);
}

void			ft_graph(t_settings *sets, t_window *win)
{
	if (!(sets->options & NCURSES))
		return ;
	if (sets->status & START)
	{
		ft_memset(win, 0, sizeof(t_window));
		init_graph();
	}
	while (!pause_game(sets, win))
		ft_graph_dump(win, sets);
	clock_gettime(CLOCK_REALTIME, &sets->time);
	ft_graph_dump(win, sets);
}
