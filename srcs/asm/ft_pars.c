/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaloul <nagaloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 15:05:07 by nagaloul          #+#    #+#             */
/*   Updated: 2017/11/23 15:39:15 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"
#include "op.h"

void	ft_preg(t_token *tok)
{
	int	i;

	i = 0;
	if (tok->unknow[0] == SEPARATOR_CHAR)
		i++;
	if (!tok->lab)
	{
		if (tok->unknow[i] == 'r')
		{
			i++;
			if (ft_atoi(&tok->unknow[i]) <= 99)
			{
				while (ft_isdigit(tok->unknow[i]))
					i++;
				if (i > 1 && (tok->unknow[i] == '\0' ||
				tok->unknow[i] == SEPARATOR_CHAR))
					tok->reg = ft_strchr(tok->unknow, 'r');
			}
		}
	}
}

void	ft_pars(t_token *tok)
{
	while (tok)
	{
		ft_comment(tok);
		ft_lab(tok);
		ft_pdirlab(tok);
		ft_pindirlab(tok);
		ft_pdir(tok);
		ft_name(tok);
		ft_ncom(tok);
		ft_pindir(tok);
		ft_preg(tok);
		ft_inst(tok);
		tok = tok->next;
	}
}
