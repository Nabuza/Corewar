/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_ocp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 10:53:43 by nolivier          #+#    #+#             */
/*   Updated: 2017/09/28 11:15:29 by nolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static unsigned char	*ft_ind_case(t_settings *sets, t_process *process,
	unsigned int *counter, unsigned int i)
{
	unsigned char	*addr;

	if (((g_op_tab + ((process->status >> 16) & 0xff) - 1)->params[i] & T_IND))
	{
		addr = ft_get_add(sets->memory, process, *counter, i);
		*counter = *counter + IND_SIZE;
		return (addr);
	}
	else
	{
		*counter = *counter + IND_SIZE;
		return (0);
	}
}

static unsigned char	*ft_dir_case(t_settings *sets, t_process *process,
	unsigned int *counter, unsigned int i)
{
	unsigned char	*addr;

	if (((g_op_tab + ((process->status >> 16) & 0xff) - 1)->params[i] & T_DIR))
	{
		addr = ft_get_add(sets->memory, process, *counter, i);
		*counter = (g_op_tab + ((process->status >> 16) & 0xff) - 1)->short_dir
		? (*counter + 2) : (*counter + DIR_SIZE);
		return (addr);
	}
	else
	{
		*counter = (g_op_tab + ((process->status >> 16) & 0xff) - 1)->short_dir
		? (*counter + 2) : (*counter + DIR_SIZE);
		return (0);
	}
}

static unsigned char	*ft_reg_case(t_settings *sets, t_process *process,
	unsigned int *counter, unsigned int i)
{
	unsigned char	*addr;

	if (((g_op_tab + ((process->status >> 16) & 0xff) - 1)->params[i] & T_REG))
	{
		addr = ft_get_add(sets->memory, process, *counter, i);
		*counter = *counter + 1;
		return (addr);
	}
	else
	{
		*counter = *counter + 1;
		return (0);
	}
}

static unsigned char	ft_verif_ocp(t_settings *sets, t_process *process,
	unsigned int *counter, unsigned char **params)
{
	unsigned int	i;
	unsigned char	code;
	unsigned char	ocp;

	i = 0xffffffff;
	ocp = sets->memory[(process->proc_counter + 1) % MEM_SIZE];
	while (++i < (g_op_tab + ((process->status >> 16) & 0xff) - 1)->num_params)
	{
		if ((code = ((sets->memory[(process->proc_counter + 1) % MEM_SIZE]
		>> ((3 - i) * 2)) & 0x3)) == REG_CODE)
			(!(params[i] = ft_reg_case(sets, process, counter, i))) ?
				(ocp = 0) : (0);
		else if (code == DIR_CODE)
			(!(params[i] = ft_dir_case(sets, process, counter, i))) ?
				(ocp = 0) : (0);
		else if (code == IND_CODE)
			(!(params[i] = ft_ind_case(sets, process, counter, i))) ?
				(ocp = 0) : (0);
		else
			ocp = 0;
	}
	return (ocp);
}

unsigned char			ft_get_ocp(t_settings *sets, t_process *process,
		unsigned int *counter, unsigned char **params)
{
	unsigned char	ocp;

	*counter = 2;
	if (!(ocp = ft_verif_ocp(sets, process, counter, params)))
		return (0);
	return (ocp);
}
