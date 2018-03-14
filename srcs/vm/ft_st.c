/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 11:55:41 by nolivier          #+#    #+#             */
/*   Updated: 2017/11/03 15:40:59 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			ft_graph_st(unsigned char *params, t_settings *sets,
	t_process *process)
{
	int		tmp;
	int		i;

	if (!(sets->options & NCURSES))
		return ;
	tmp = params - sets->memory;
	i = 0;
	while (i < REG_SIZE)
	{
		sets->info_mem[((tmp + i) % MEM_SIZE) * 3] =
		(sets->info_mem[((tmp + i) % MEM_SIZE) * 3] & 0xf0) |
		((process->status >> 24) & 0xf);
		sets->info_mem[((tmp + i) % MEM_SIZE) * 3 + 2] |=
		(STORE_TIME & 0x7f);
		i++;
	}
}

static void			ft_print_st(t_process *process, t_settings *sets)
{
	int				tmp;
	int				i;

	if (!((sets->options & VERBOSITY) && (sets->options & OPERATIONS)))
		return ;
	tmp = 0;
	if (((sets->memory[process->proc_counter + 1] >> 4) & 0x3) == REG_CODE)
	{
		ft_printf("P%5d | st r%d %d\n", process->num,
		sets->memory[(process->proc_counter + 2) % MEM_SIZE],
		sets->memory[(process->proc_counter + 3) % MEM_SIZE]);
	}
	else
	{
		i = 0xffffffff;
		while (++i < 4 && i < IND_SIZE)
			tmp |= (sets->memory[(process->proc_counter + 3 + i) % MEM_SIZE]
			<< (8 * (IND_SIZE - 1 - i)));
		tmp = (!(0x8000 & tmp)) ? tmp : -(tmp ^ 0xffff) - 1;
		ft_printf("P%5d | st r%d %d\n", process->num,
		sets->memory[(process->proc_counter + 2) % MEM_SIZE], tmp);
	}
}

static void			ft_put_reg(unsigned char **params, t_process *process)
{
	unsigned int		i;

	i = 0;
	while (i < REG_SIZE)
	{
		params[1][REG_SIZE - 1 - i] = params[0][REG_SIZE - 1 - i];
		i++;
	}
	ft_modif_carry_reg(process, params[1], 3);
}

static void			ft_put_ind(unsigned char **params,
	unsigned char *memory, t_process *process)
{
	unsigned int		i;

	i = 0;
	while (i < REG_SIZE && i < DIR_SIZE)
	{
		memory[(params[1] - memory + (DIR_SIZE - 1 - i)) % MEM_SIZE] =
		params[0][REG_SIZE - 1 - i];
		i++;
	}
	while (i < DIR_SIZE)
	{
		memory[(params[1] - memory + (DIR_SIZE - 1 - i)) % MEM_SIZE] = 0;
		i++;
	}
	ft_modif_carry_reg(process, params[0], 3);
}

int					ft_st(t_settings *sets, t_process *process,
	t_process **begin)
{
	unsigned char		ocp;
	unsigned char		code;
	unsigned int		counter;
	unsigned char		*params[2];

	if (++process->cycle_count < (g_op_tab + 2)->cycles)
		return (1);
	if (!(ocp = ft_get_ocp(sets, process, &counter, params)))
	{
		ft_pc_move(process, sets, counter);
		return (0);
	}
	ft_print_st(process, sets);
	if ((code = ((ocp >> 4) & 0x3)) == REG_CODE)
		ft_put_reg(params, process);
	else if (code == IND_CODE)
	{
		ft_put_ind(params, sets->memory, process);
		ft_graph_st(params[1], sets, process);
	}
	ft_pc_move(process, sets, counter);
	ft_graph_process(process, sets);
	return (1);
	(void)begin;
}
