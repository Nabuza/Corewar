/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaloul <nagaloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 13:36:30 by nagaloul          #+#    #+#             */
/*   Updated: 2017/11/17 17:20:32 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		ft_sub(t_token *tok, int i, t_token *lab, t_list *sep)
{
	lab = NULL;
	if (!ft_reg(tok, i))
	{
		ft_puterror(tok->next, 1, i, tok);
		return (0);
	}
	if (!ft_reg(tok->next, i))
	{
		ft_puterror(tok->next->next, 2, i, tok);
		return (0);
	}
	if (!ft_reg(tok->next->next, i))
	{
		ft_puterror(tok->next->next->next, 2, i, tok);
		return (0);
	}
	if (!ft_tomuch(tok->next->next->next, i))
		return (0);
	if (!ft_virgule(i, sep, 3, tok->inst))
	{
		ft_puterrorsep(i);
		return (0);
	}
	return (1);
}

int		ft_st(t_token *tok, int i, t_token *lab, t_list *sep)
{
	if (!ft_reg(tok, i))
	{
		ft_puterror(tok->next, 1, i, tok);
		return (0);
	}
	if (!ft_reg(tok->next, i) && !ft_indir(tok->next, i, lab))
	{
		ft_puterror(tok->next->next, 2, i, tok);
		return (0);
	}
	if (!ft_tomuch(tok->next->next, i))
		return (0);
	if (!ft_virgule(i, sep, 2, tok->inst))
	{
		ft_puterrorsep(i);
		return (0);
	}
	return (1);
}

int		ft_ld(t_token *tok, int i, t_token *lab, t_list *sep)
{
	if (!ft_dir(tok, i, lab) && !ft_indir(tok, i, lab))
	{
		ft_puterror(tok->next, 1, i, tok);
		return (0);
	}
	if (!ft_reg(tok->next, i))
	{
		ft_puterror(tok->next->next, 2, i, tok);
		return (0);
	}
	if (!ft_tomuch(tok->next->next, i))
		return (0);
	if (!ft_virgule(i, sep, 2, tok->inst))
	{
		ft_puterrorsep(i);
		return (0);
	}
	return (1);
}

int		ft_live(t_token *tok, int i, t_token *temp, t_list *sep)
{
	if (!ft_dir(tok, i, temp))
	{
		ft_puterror(tok->next, 1, i, tok);
		return (0);
	}
	if (!ft_tomuch(tok->next, i))
		return (0);
	if (!ft_virgule(i, sep, 1, tok->inst))
	{
		ft_puterrorsep(i);
		return (0);
	}
	return (1);
}
