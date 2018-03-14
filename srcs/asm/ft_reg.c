/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 15:51:19 by nagaloul          #+#    #+#             */
/*   Updated: 2017/10/30 13:33:31 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		ft_indir(t_token *tok, int i, t_token *temp)
{
	tok = tok->next;
	if (!tok || tok->lan != i || (!tok->indir && !tok->indirlab))
		return (0);
	if (tok->indirlab && !ft_indirlab(tok->indirlab, temp))
		return (0);
	return (1);
}

int		ft_indirlab(char *tok, t_token *temp)
{
	while (temp)
	{
		if (temp->lab)
			if (!ft_strcmp(temp->lab, tok))
				return (1);
		temp = temp->next;
	}
	return (0);
}

int		ft_dirlab(char *tok, t_token *temp)
{
	while (temp)
	{
		if (temp->lab)
			if (!ft_strcmp(temp->lab, tok))
				return (1);
		temp = temp->next;
	}
	return (0);
}

int		ft_dir(t_token *tok, int i, t_token *temp)
{
	tok = tok->next;
	if (!tok || tok->lan != i || (!tok->dir && !tok->dirlab))
		return (0);
	if (tok->dirlab && !ft_dirlab(tok->dirlab, temp))
		return (0);
	return (1);
}

int		ft_reg(t_token *tok, int i)
{
	tok = tok->next;
	if (!tok || tok->lan != i || !tok->reg)
		return (0);
	return (1);
}
