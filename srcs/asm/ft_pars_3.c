/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:38:02 by adenis            #+#    #+#             */
/*   Updated: 2017/11/22 17:58:53 by nagaloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	ft_pindir(t_token *tok)
{
	int i;
	int a;

	a = 0;
	i = 0;
	if (!tok->lab)
		if (onlysep(&tok))
		{
			if (tok->unknow[0] == SEPARATOR_CHAR)
				i++;
			a = i;
			if (tok->unknow[i] == '-')
				i++;
			if (ft_isdigit(tok->unknow[i]))
			{
				while (ft_isdigit(tok->unknow[i]))
					i++;
				if (tok->unknow[i] == '\0' || tok->unknow[i] == SEPARATOR_CHAR)
				{
					tok->indir = &tok->unknow[a];
					if (ft_strchr(tok->indir, SEPARATOR_CHAR))
						*ft_strchr(tok->indir, SEPARATOR_CHAR) = '\0';
				}
			}
		}
}

void	ft_name(t_token *tok)
{
	if (!ft_strcmp(tok->unknow, NAME_CMD_STRING))
		tok->name = tok->unknow;
}

void	ft_ncom(t_token *tok)
{
	if (!ft_strcmp(tok->unknow, COMMENT_CMD_STRING))
		tok->ncom = tok->unknow;
}

void	ft_pdir(t_token *tok)
{
	int i;

	i = 0;
	if (onlysep(&tok))
	{
		if (tok->unknow[0] == SEPARATOR_CHAR)
			i++;
		if (!tok->dirlab)
			if (tok->unknow[i] == DIRECT_CHAR)
			{
				i++;
				if (tok->unknow[i] == '-')
					i++;
				while (ft_isdigit(tok->unknow[i]))
					i++;
				if (tok->unknow[i] == '\0' || tok->unknow[i] == SEPARATOR_CHAR)
				{
					tok->dir = ft_strchr(tok->unknow, DIRECT_CHAR);
					if (ft_strchr(tok->dir, SEPARATOR_CHAR))
						*ft_strchr(tok->dir, SEPARATOR_CHAR) = '\0';
				}
			}
	}
}

void	ft_inst(t_token *tok)
{
	int i;

	i = 0;
	if (!tok->lab && !tok->comment)
	{
		if (!onlysep(&tok))
			tok->inst = tok->unknow;
		else
		{
			if (tok->unknow[0] == SEPARATOR_CHAR)
				i++;
			tok->inst = &tok->unknow[i];
			if (ft_strchr(tok->inst, SEPARATOR_CHAR))
				*ft_strchr(tok->inst, SEPARATOR_CHAR) = '\0';
		}
	}
}
