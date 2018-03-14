/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_winner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 15:43:56 by khabbar           #+#    #+#             */
/*   Updated: 2017/11/03 15:44:02 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			ft_print_winner(t_settings *sets, t_window *win)
{
	if (!(sets->status & GAME_CANCELED))
	{
		if (!(sets->options & NCURSES))
		{
			ft_printf("Contestant %d, \"%s\", has won !\n",
				(sets->status >> (8 * 3)) & 0xff, (sets->champs +
				((sets->status >> (8 * 3)) & 0xff) - 1)->prog_name);
		}
		else
		{
			ft_graph_end_audio(sets);
			while (getch() == ERR)
				ft_graph_dump(win, sets);
		}
	}
}
