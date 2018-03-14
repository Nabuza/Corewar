/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_dump.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 15:24:06 by khabbar           #+#    #+#             */
/*   Updated: 2017/11/03 15:33:53 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			ft_define_color(t_settings *sets, t_window *win,
	unsigned char *tmp, int s)
{
	if (sets->info_mem[3 * s + 1] & 0x7f)
	{
		*tmp = ((sets->info_mem[3 * s] >> 4) & 0x0f) + 10;
		wattron(win->mem, COLOR_PAIR(*tmp) | A_DIM | A_STANDOUT | A_BOLD);
	}
	else if ((sets->info_mem[3 * s + 2] & 0x80) ||
	(sets->info_mem[3 * s + 1] & 0x80))
	{
		*tmp = (sets->info_mem[3 * s] & 0xf);
		wattron(win->mem, COLOR_PAIR(*tmp) | A_STANDOUT);
	}
	else if (sets->info_mem[3 * s + 2] & 0x7f)
	{
		*tmp = (sets->info_mem[3 * s] & 0x0f);
		wattron(win->mem, COLOR_PAIR(*tmp) | A_DIM | A_BOLD);
	}
	else if (sets->info_mem[3 * s] & 0xf)
	{
		*tmp = (sets->info_mem[3 * s] & 0x0f);
		wattron(win->mem, COLOR_PAIR(*tmp));
	}
}

static void			ft_graph_color(t_settings *sets, t_window *win, int i)
{
	unsigned char	tmp;
	char			*b;
	int				j;

	b = "0123456789abcdef";
	j = -1;
	while (++j < LINE_SIZE && i + j < MEM_SIZE)
	{
		tmp = 0;
		wprintw(win->mem, " ");
		ft_define_color(sets, win, &tmp, i + j);
		wprintw(win->mem, "%C%C", sets->options & NCURSES_S ? L'♥' :
		b[sets->memory[i + j] / 16], sets->options & NCURSES_S ? L'♥' :
		b[sets->memory[i + j] % 16]);
		wattroff(win->mem, COLOR_PAIR(tmp)
		| A_DIM | A_BOLD | A_STANDOUT | A_REVERSE);
		if (!(sets->status & PAUSE) && sets->info_mem[3 * (i + j) + 1] & 0x80)
			sets->info_mem[3 * (i + j) + 1] &= ~0x80;
		if (!(sets->status & PAUSE) && sets->info_mem[3 * (i + j) + 2] & 0x80)
			sets->info_mem[3 * (i + j) + 2] &= ~0x80;
		if (!(sets->status & PAUSE) && sets->info_mem[3 * (i + j) + 1] & 0x7f)
			sets->info_mem[3 * (i + j) + 1]--;
		if (!(sets->status & PAUSE) && sets->info_mem[3 * (i + j) + 2] & 0x7f)
			sets->info_mem[3 * (i + j) + 2]--;
	}
}

void				ft_graph_dump(t_window *win, t_settings *sets)
{
	int				i;
	int				y;

	if (LINE_SIZE < 1)
		return ;
	if (!win->mem && !(win->mem = newwin(66, 195, 1, 1)))
		exit(EXIT_FAILURE);
	i = 0;
	y = 1;
	box(win->mem, 0, 0);
	wmove(win->mem, y, 1);
	while (i < MEM_SIZE)
	{
		ft_graph_color(sets, win, i);
		i += LINE_SIZE;
		if (++y < MEM_SIZE - 1)
			wmove(win->mem, y, 1);
	}
	wrefresh(win->mem);
	delwin(win->mem);
	win->mem = NULL;
	if (COLS > 251)
		ft_graph_info(win, sets);
}
