/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_graph.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 13:44:41 by khabbar           #+#    #+#             */
/*   Updated: 2017/11/03 15:22:39 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_unset_graph(t_settings *sets)
{
	if (sets->options & NCURSES)
	{
		curs_set(1);
		endwin();
	}
}

void		ft_init_graph(t_settings *sets)
{
	unsigned int	i;
	unsigned int	j;

	if (!(sets->options & NCURSES))
		return ;
	i = 0;
	sets->deaths_proc = 0;
	ft_memset(sets->info_mem, 0, (3 * MEM_SIZE));
	sets->speed_limit = INIT_SPEED;
	sets->cycle_time = 1000000000 / INIT_SPEED;
	while (i < sets->nb_champs)
	{
		sets->info_mem[3 * i * (MEM_SIZE / sets->nb_champs) + 1] |= 0x80;
		j = 0;
		while (j < (sets->champs[i].prog_size))
		{
			sets->info_mem[3 * i * (MEM_SIZE / sets->nb_champs) + 3 * j] |=
			i + 1;
			j++;
		}
		i++;
	}
}
