/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 11:54:44 by nolivier          #+#    #+#             */
/*   Updated: 2017/09/12 14:43:52 by nolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		ft_print_aff(t_settings *sets, char aff)
{
	if (!(sets->options & AFF_OUTPUT))
		return ;
	ft_putstr("Aff: ");
	write(1, &aff, 1);
	write(1, "\n", 1);
}

int				ft_aff(t_settings *sets, t_process *process, t_process **begin)
{
	unsigned char	ocp;
	unsigned int	counter;
	unsigned char	aff;
	unsigned char	*params[1];

	if (++process->cycle_count < (g_op_tab + 15)->cycles)
		return (1);
	if (!(ocp = ft_get_ocp(sets, process, &counter, params)))
	{
		ft_pc_move(process, sets, counter);
		return (0);
	}
	aff = *(params[0] + 3);
	ft_print_aff(sets, aff);
	ft_pc_move(process, sets, counter);
	ft_graph_process(process, sets);
	return (1);
	(void)begin;
}
