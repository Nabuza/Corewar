/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 11:56:01 by nolivier          #+#    #+#             */
/*   Updated: 2017/11/03 15:36:58 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	ft_print_ldi(t_process *process, unsigned char **params,
	t_settings *sets, unsigned int counter)
{
	int				tmp1;
	int				tmp2;
	int				tmp3;

	if (!((sets->options & VERBOSITY) && (sets->options & OPERATIONS)))
		return ;
	tmp1 = ft_get_val(process, params[0], sets->memory, 1);
	tmp2 = ft_get_val(process, params[1], sets->memory, 2);
	tmp3 = tmp1 + tmp2;
	ft_printf("P%5d | ldi %d %d r%d\n       | -> load from %d + %d = %d "
	"(with pc and mod %d)\n", process->num, tmp1, tmp2,
	sets->memory[(process->proc_counter + counter - 1) % MEM_SIZE], tmp1, tmp2,
	tmp3, process->proc_counter + (tmp3 % IDX_MOD));
}

static void	ft_put_reg(unsigned char **params, t_process *process,
	unsigned char *memory)
{
	unsigned int	i;
	unsigned int	s1;
	unsigned int	s2;

	s1 = ft_get_val(process, params[0], memory, 1);
	s2 = ft_get_val(process, params[1], memory, 2);
	s1 = s1 + s2;
	i = 0xffffffff;
	while (++i < REG_SIZE)
	{
		params[2][i] = !(s1 & 0x80000000) ?
			memory[(process->proc_counter + (s1 % IDX_MOD) + i) % MEM_SIZE] :
			memory[(process->proc_counter - (-s1 % IDX_MOD) + i) % MEM_SIZE];
	}
	ft_modif_carry_reg(process, params[2], 10);
}

int			ft_ldi(t_settings *sets, t_process *process, t_process **begin)
{
	unsigned char	ocp;
	unsigned int	counter;
	unsigned char	*params[3];

	if (++process->cycle_count < (g_op_tab + 9)->cycles)
		return (1);
	if (!(ocp = ft_get_ocp(sets, process, &counter, params)))
	{
		ft_pc_move(process, sets, counter);
		return (0);
	}
	ft_print_ldi(process, params, sets, counter);
	ft_put_reg(params, process, sets->memory);
	ft_pc_move(process, sets, counter);
	ft_graph_process(process, sets);
	return (1);
	(void)begin;
}
