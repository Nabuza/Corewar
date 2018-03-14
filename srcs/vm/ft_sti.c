/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 11:57:55 by nolivier          #+#    #+#             */
/*   Updated: 2017/11/03 15:39:36 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		ft_graph_sti(t_process *process, unsigned char **params,
	t_settings *sets)
{
	int				tmp;
	int				i;

	tmp = ft_get_val(process, params[1], sets->memory, 2) +
	ft_get_val(process, params[2], sets->memory, 3);
	i = 0;
	while (i < REG_SIZE)
	{
		sets->info_mem[((process->proc_counter + tmp + i) % MEM_SIZE) * 3] =
		(sets->info_mem[((process->proc_counter + tmp + i) % MEM_SIZE) * 3] &
		0xf0) | ((process->status >> 24) & 0xf);
		sets->info_mem[((process->proc_counter + tmp + i) % MEM_SIZE)
		* 3 + 2] |= (STORE_TIME & 0x7f);
		i++;
	}
}

static void		ft_print_sti(t_process *process, unsigned char **params,
	t_settings *sets)
{
	int				tmp1;
	int				tmp2;
	int				tmp3;

	if ((sets->options & NCURSES))
	{
		ft_graph_sti(process, params, sets);
		return ;
	}
	if (!((sets->options & VERBOSITY) && (sets->options & OPERATIONS)))
		return ;
	tmp1 = ft_get_val(process, params[1], sets->memory, 2);
	tmp2 = ft_get_val(process, params[2], sets->memory, 3);
	tmp3 = tmp1 + tmp2;
	ft_printf("P%5d | sti r%d %d %d\n       | -> store to %d + %d = %d "
	"(with pc and mod %d)\n", process->num,
	sets->memory[(process->proc_counter + 2) % MEM_SIZE], tmp1, tmp2,
	tmp1, tmp2, tmp3, process->proc_counter + (tmp3 % IDX_MOD));
}

static void		ft_put_ind(unsigned char **params, t_process *process,
	unsigned char *memory)
{
	unsigned int	i;
	int				s2;
	int				s3;

	s2 = ft_get_val(process, params[1], memory, 2);
	s3 = ft_get_val(process, params[2], memory, 3);
	s2 = s2 + s3;
	i = 0xffffffff;
	while (++i < REG_SIZE)
		!(s2 & 0x80000000) ? (memory[(process->proc_counter +
			(s2 % IDX_MOD) + i) % MEM_SIZE] = params[0][i]) :
			(memory[(process->proc_counter - (-s2 % IDX_MOD) + i) % MEM_SIZE] =
			params[0][i]);
	ft_modif_carry_reg(process, params[0], 11);
}

int				ft_sti(t_settings *sets, t_process *process, t_process **begin)
{
	unsigned char		ocp;
	unsigned int		counter;
	unsigned char		*params[3];

	if (++process->cycle_count < (g_op_tab + 10)->cycles)
		return (1);
	if (!(ocp = ft_get_ocp(sets, process, &counter, params)))
	{
		ft_pc_move(process, sets, counter);
		return (0);
	}
	ft_print_sti(process, params, sets);
	ft_put_ind(params, process, sets->memory);
	ft_pc_move(process, sets, counter);
	ft_graph_process(process, sets);
	return (1);
	(void)begin;
}
