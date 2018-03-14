/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_val.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 14:53:19 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/19 15:31:41 by nolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_get_val(t_process *process, unsigned char *addr,
	unsigned char *memory, unsigned int param)
{
	int				tmp;
	unsigned int	i;
	unsigned char	code;

	tmp = 0;
	i = 0xffffffff;
	if ((code = memory[(process->proc_counter + 1) % MEM_SIZE] >>
		(6 - ((param - 1) * 2)) & 0x3) == REG_CODE)
	{
		while (++i < REG_SIZE && i < 4)
			tmp |= addr[i] << (8 * (REG_SIZE - 1 - i));
	}
	else if ((!(g_op_tab + ((process->status >> 16) & 0xff) - 1)->short_dir)
		|| code == IND_CODE)
		while (++i < DIR_SIZE)
			tmp |= memory[(addr - memory + i) % MEM_SIZE] <<
				(8 * (DIR_SIZE - 1 - i));
	else
	{
		while (++i < 2)
			tmp |= memory[(addr - memory + i) % MEM_SIZE] << (8 * (1 - i));
		if (tmp & 0x8000)
			tmp = -(tmp ^ 0xffff) - 1;
	}
	return (tmp);
}
