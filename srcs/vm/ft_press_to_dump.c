/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_press_to_dump.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 13:06:51 by khabbar           #+#    #+#             */
/*   Updated: 2017/11/03 15:19:25 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	init_dump(SCREEN **scr)
{
	if (!(*scr) && !((*scr) = newterm(NULL, stdin, stdout)))
		return ;
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	while (getch() == ERR)
		;
	endwin();
}

void		ft_press_to_dump(t_settings *sets, SCREEN **scr)
{
	ft_dump_memory(sets->memory, MEM_SIZE);
	write(1, "\n", 1);
	init_dump(scr);
}
