/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 17:22:57 by adenis            #+#    #+#             */
/*   Updated: 2017/11/11 19:57:17 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		opc_val(int type)
{
	if (type == 1)
		return (REG_CODE);
	if (type == 4)
		return (DIR_CODE);
	if (type == 6 || type == 5)
		return (IND_CODE);
	return (2);
}

int		ft_opc(t_output *pop)
{
	int			opc;
	int			i;
	int			val;
	t_output	*tmp;

	val = 64;
	opc = 0;
	i = g_op_tab[whichop(pop->name)].num_params;
	tmp = pop;
	while (i)
	{
		tmp = tmp->next;
		opc += val * (opc_val(tmp->type));
		val = val / 4;
		i--;
	}
	return (opc);
}

void	printout(void)
{
	t_output *tmp;

	tmp = OUT;
	while (tmp)
	{
		if (tmp->type == 9 || tmp->type == 0)
			ft_printf("\n");
		ft_printf("\e[32m%s\e[0m [%d] ", tmp->name, tmp->size);
		tmp = tmp->next;
	}
}

void	ft_calc(t_token *tok)
{
	create_output(tok);
	fill_dirlab();
	print_header();
	print_val();
}
