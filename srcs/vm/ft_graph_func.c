/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 15:26:57 by khabbar           #+#    #+#             */
/*   Updated: 2017/11/03 15:34:53 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_graph_time(t_settings *sets)
{
	struct timespec		tp;

	if (!(sets->options & NCURSES))
		return ;
	clock_gettime(CLOCK_REALTIME, &tp);
	while ((tp.tv_sec - sets->time.tv_sec) * 1000000000 +
	(tp.tv_nsec - sets->time.tv_nsec) < sets->cycle_time)
		clock_gettime(CLOCK_REALTIME, &tp);
	sets->time.tv_sec = tp.tv_sec;
	sets->time.tv_nsec = tp.tv_nsec;
}

void		ft_graph_winner(t_window *win, t_settings *sets)
{
	win->y++;
	mvwprintw(win->info, ++(win->y), (win->x = 3), "The winner is:");
	wattron(win->info, COLOR_PAIR((sets->status >> (8 * 3)) & 0xff));
	mvwprintw(win->info, (win->y)++, (win->x = 18), "%s",
	(sets->champs + ((sets->status >> (8 * 3)) & 0xff) - 1)->prog_name);
	wattroff(win->info, COLOR_PAIR((sets->status >> (8 * 3)) & 0xff));
	wattron(win->info, COLOR_PAIR(5));
	mvwprintw(win->info, ++(win->y), (win->x = 3), "Press any key to finish.");
}

static void	ft_breakdown(t_window *win, char *buf, int nbr, int i)
{
	buf[nbr] = 0;
	wattron(win->info, COLOR_PAIR(i >= 0 ? (i + 1) : 0));
	mvwprintw(win->info, win->y, win->x, "%s", buf);
	wattroff(win->info, COLOR_PAIR(i >= 0 ? (i + 1) : 0));
	buf[nbr] = '|';
	win->x += nbr;
}

static void	ft_print_breakdown(t_window *win, t_settings *sets, int mod,
	unsigned int total)
{
	char			buf[51];
	unsigned int	i;
	unsigned int	nbr;

	ft_memset(buf, '|', 50);
	buf[50] = 0;
	if (!total)
	{
		mvwprintw(win->info, win->y, win->x, "%s", buf);
		win->x += 50;
	}
	else
	{
		i = 0xffffffff;
		while (++i < sets->nb_champs)
		{
			if (i && i == sets->nb_champs - 1)
				nbr = 50 - (win->x - 4);
			else
				nbr = !mod ? (sets->lives[i].current_period * 50 / total) :
				(sets->lives[i].last_period * 50 / total);
			ft_breakdown(win, buf, nbr, i);
		}
	}
}

void		ft_live_breakdown(t_window *win, t_settings *sets, char *msg,
	int mod)
{
	unsigned int	i;
	unsigned int	total;

	i = 0xffffffff;
	total = 0;
	while (++i < sets->nb_champs)
		total += !mod ? sets->lives[i].current_period :
		sets->lives[i].last_period;
	mvwprintw(win->info, win->y, (win->x = 3), "%s", msg);
	mvwprintw(win->info, ++(win->y), (win->x)++, "[");
	ft_print_breakdown(win, sets, mod, total);
	wattron(win->info, COLOR_PAIR(5));
	mvwprintw(win->info, win->y, win->x, "]");
	win->y += 2;
}
