/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 16:38:08 by adenis            #+#    #+#             */
/*   Updated: 2017/10/30 13:42:26 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		whichop(char *s)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(s, g_op_tab[i].label))
			return (i);
		i++;
	}
	return (0);
}

int		isop(char *s)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(s, g_op_tab[i].label))
			return (1);
		i++;
	}
	return (0);
}

int		get_value(t_token *token)
{
	int		i;

	i = 0;
	if (token->lab)
		return (i);
	if ((++i) && token->reg)
		return (i);
	if ((++i) && token->comment)
		return (i);
	if ((++i) && token->dirlab)
		return (i);
	if ((++i) && token->dir)
		return (i);
	if ((++i) && token->indirlab)
		return (i);
	if ((++i) && token->indir)
		return (i);
	if ((++i) && token->name)
		return (i);
	if ((++i) && token->ncom)
		return (i);
	if ((++i) && token->inst)
		return (i);
	return (-1);
}
