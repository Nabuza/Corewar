/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaloul <nagaloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 20:26:49 by nagaloul          #+#    #+#             */
/*   Updated: 2017/11/22 14:15:29 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

static int		ft_howmany(t_token *tok, int i, int a, t_token *temp)
{
	if (tok && !ft_strcmp(tok->unknow, ","))
	{
		ft_puterrorsep(tok->lan);
		return (0);
	}
	if (i == 1)
		if (!tok || tok->lan != a)
		{
			ft_printf("Syntax error at token [TOKEN][%d] ENDLINE\n",\
			temp->lan);
			return (0);
		}
	if (i == 2)
		if (!tok || tok->lan != a)
		{
			ft_printf("Invalid parameter count for instruction %s\n",\
			temp->inst);
			return (0);
		}
	return (1);
}

void			ft_puterror(t_token *tok, int i, int a, t_token *temp)
{
	if (!ft_howmany(tok, i, a, temp))
		return ;
	if (tok->dirlab)
		ft_printf("Syntax error at token [TOKEN][%d:%d] DIRECT_LABEL \"%s\"\n",\
			tok->lan, tok->col, tok->dirlab);
	else if (tok->dir)
		ft_printf("Syntax error at token [TOKEN][%d:%d] DIRECT \"%s\"\n", \
			tok->lan, tok->col, tok->dir);
	else if (tok->indirlab)
		ft_printf("Syntax error at token [TOKEN][%d:%d] INDIRECT_LABEL \"%s\"\
			\n", tok->lan, tok->col, tok->indirlab);
	else if (tok->indir)
		ft_printf("Syntax error at token [TOKEN][%d:%d] INDIRECT \"%s\"\n", \
		tok->lan, tok->col, tok->indir);
	else if (tok->reg)
		ft_printf("Syntax error at token [TOKEN][%d:%d] REGISTRE \"%s\"\n", \
		tok->lan, tok->col, tok->reg);
	else if (tok->lab)
		ft_printf("Syntax error at token [TOKEN][%d:%d] LABEL \"%s\"\n", \
		tok->lan, tok->col, tok->lab);
	else if (tok->inst)
		ft_printf("Syntax error at token [TOKEN][%d:%d] INSTRUCTION \"%s\"\n", \
		tok->lan, tok->col, tok->inst);
	else
		ft_printf("Error\n");
}
