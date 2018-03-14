/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 13:31:12 by khabbar           #+#    #+#             */
/*   Updated: 2017/11/03 15:21:58 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_graph_process(t_process *process, t_settings *sets)
{
	if (!(sets->status & NCURSES))
		return ;
	sets->info_mem[process->proc_counter * 3 + 2] &= ~0x80;
}
