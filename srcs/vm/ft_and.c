/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 11:55:00 by nolivier          #+#    #+#             */
/*   Updated: 2017/09/28 11:04:49 by nolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			ft_print_and(t_process *process, unsigned char **params,
	t_settings *sets, unsigned char counter)
{
	unsigned int	tmp1;
	unsigned int	tmp2;

	if (!((sets->options & VERBOSITY) && (sets->options & OPERATIONS)))
		return ;
	tmp1 = ft_get_val(process, params[0], sets->memory, 1);
	tmp2 = ft_get_val(process, params[1], sets->memory, 2);
	ft_printf("P%5d | and %d %d r%d\n", process->num, tmp1, tmp2,
	sets->memory[(process->proc_counter + counter - 1) % MEM_SIZE]);
}

static void			ft_put_reg(unsigned char **params, unsigned char ocp,
	t_process *process, unsigned char *memory)
{
	unsigned int	i;
	unsigned char	s1;
	unsigned char	s2;

	i = 0;
	while (i < REG_SIZE)
	{
		s1 = (!(((ocp >> 6) & 0x3) == REG_CODE)) ?
			memory[(params[0] - memory + i) % MEM_SIZE] : params[0][i];
		s2 = (!(((ocp >> 4) & 0x3) == REG_CODE)) ?
			memory[(params[1] - memory + i) % MEM_SIZE] : params[1][i];
		params[2][i] = s1 & s2;
		i++;
	}
	ft_modif_carry_reg(process, params[2], 6);
}

int					ft_and(t_settings *sets, t_process *process,
	t_process **begin)
{
	unsigned char	ocp;
	unsigned int	counter;
	unsigned char	*params[3];

	if (++process->cycle_count < (g_op_tab + 5)->cycles)
		return (1);
	if (!(ocp = ft_get_ocp(sets, process, &counter, params)))
	{
		ft_pc_move(process, sets, counter);
		return (0);
	}
	ft_print_and(process, params, sets, counter);
	ft_put_reg(params, ocp, process, sets->memory);
	ft_pc_move(process, sets, counter);
	ft_graph_process(process, sets);
	return (1);
	(void)begin;
}
