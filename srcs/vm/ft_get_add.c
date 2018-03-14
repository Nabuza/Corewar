/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 13:55:35 by nolivier          #+#    #+#             */
/*   Updated: 2017/09/28 11:13:14 by nolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned char		*ft_get_reg(unsigned char *memory, t_process *process,
	unsigned int counter)
{
	unsigned char		*ptr;
	unsigned int		reg_num;

	reg_num = memory[(process->proc_counter + counter) % MEM_SIZE];
	if (!(reg_num > 0 && reg_num < 17))
		return (0);
	ptr = process->registers + ((reg_num - 1) * REG_SIZE);
	return (ptr);
}

unsigned char		*ft_get_dir(unsigned char *memory, t_process *process,
	unsigned int counter)
{
	unsigned char		*ptr;

	ptr = memory + ((process->proc_counter + counter) % MEM_SIZE);
	return (ptr);
}

unsigned char		*ft_get_ind_mod(unsigned char *memory, t_process *process,
	unsigned int counter)
{
	unsigned char		*ptr;
	unsigned int		ind_counter;
	int					i;

	ind_counter = 0;
	i = 0;
	while (i < IND_SIZE && i < 4)
	{
		ind_counter += (memory[(process->proc_counter + counter + i)
				% MEM_SIZE] << ((IND_SIZE - 1 - i) * 8));
		i++;
	}
	ptr = (!(ind_counter & (0x80 << ((IND_SIZE - 1) * 8)))) ?
		(memory + ((process->proc_counter +
					(ind_counter % IDX_MOD)) % MEM_SIZE)) :
		(memory + ((process->proc_counter -
					(((ind_counter ^ 0xffff) + 1) % IDX_MOD)) % MEM_SIZE));
	return (ptr);
}

unsigned char		*ft_get_ind(unsigned char *memory, t_process *process,
	unsigned int counter)
{
	unsigned char		*ptr;
	unsigned int		ind_counter;
	int					i;

	ind_counter = 0;
	i = 0;
	while (i < IND_SIZE && i < 4)
	{
		ind_counter += (memory[(process->proc_counter + counter + i)
				% MEM_SIZE] << ((IND_SIZE - 1 - i) * 8));
		i++;
	}
	ptr = (!(ind_counter & (0x80 << ((IND_SIZE - 1) * 8)))) ?
		(memory + ((process->proc_counter +
					ind_counter) % MEM_SIZE)) :
		(memory + ((process->proc_counter -
					((ind_counter ^ 0xffff) + 1)) % MEM_SIZE));
	return (ptr);
}

unsigned char		*ft_get_add(unsigned char *memory, t_process *process,
	unsigned int counter, unsigned int param_num)
{
	unsigned int		code;

	if ((code = (memory[(process->proc_counter + 1) % MEM_SIZE]
			>> ((3 - param_num) * 2)) & 0x3) == REG_CODE)
		return (ft_get_reg(memory, process, counter));
	else if (code == DIR_CODE)
		return (ft_get_dir(memory, process, counter));
	else if (code == IND_CODE)
		return (((g_fct_tab +
			((process->status >> 16) & 0xff) - 1)->add_restrict) ?
			ft_get_ind_mod(memory, process, counter) :
			ft_get_ind(memory, process, counter));
	else
		return (0);
}
