/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:37:59 by adenis            #+#    #+#             */
/*   Updated: 2017/11/22 16:52:29 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		onlysep(t_token **tok)
{
	int i;

	i = 0;
	while ((*tok)->unknow[i])
	{
		if ((*tok)->unknow[i] == SEPARATOR_CHAR ||
				(*tok)->unknow[i] == LABEL_CHAR
			|| (*tok)->unknow[i] == DIRECT_CHAR)
			i++;
		else
			return (1);
	}
	return (0);
}

void	ft_comment(t_token *tok)
{
	if (ft_countchar(tok->unknow, '"') == 2)
		tok->comment = tok->unknow;
}

void	ft_lab(t_token *tok)
{
	int i;

	i = 0;
	if (!ft_strchr(tok->unknow, DIRECT_CHAR))
	{
		if (onlysep(&tok))
		{
			while (tok->unknow[i])
				i++;
			i--;
			if (tok->unknow[i] == LABEL_CHAR)
			{
				tok->unknow[i] = '\0';
				tok->lab = tok->unknow;
			}
		}
	}
}

void	ft_pindirlab(t_token *tok)
{
	int	i;

	i = 0;
	if (onlysep(&tok))
	{
		if (tok->unknow[0] == SEPARATOR_CHAR)
			i++;
		if (tok->unknow[i] == LABEL_CHAR)
		{
			tok->indirlab = &tok->unknow[i + 1];
			if (ft_strchr(tok->indirlab, SEPARATOR_CHAR))
				*ft_strchr(tok->indirlab, SEPARATOR_CHAR) = '\0';
		}
	}
}

void	ft_pdirlab(t_token *tok)
{
	int	i;

	i = 0;
	if (onlysep(&tok))
	{
		if (tok->unknow[0] == SEPARATOR_CHAR)
			i++;
		if (tok->unknow[i] == DIRECT_CHAR && tok->unknow[i + 1] == LABEL_CHAR)
		{
			tok->dirlab = &tok->unknow[i + 2];
			if (ft_strchr(tok->dirlab, SEPARATOR_CHAR))
				*ft_strchr(tok->dirlab, SEPARATOR_CHAR) = '\0';
		}
	}
}
