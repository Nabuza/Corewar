/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:37:00 by adenis            #+#    #+#             */
/*   Updated: 2017/11/22 14:22:35 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		check_com_l(char *s)
{
	if (ft_strlen(s) - 2 > COMMENT_LENGTH)
	{
		ft_printf("Champion comment too long (Max length %d)\n",\
			COMMENT_LENGTH);
		clean();
	}
	return (1);
}

int		check_name_l(char *s)
{
	if (ft_strlen(s) - 2 > PROG_NAME_LENGTH)
	{
		ft_printf("Champion name too long (Max lenght %d)\n", PROG_NAME_LENGTH);
		clean();
	}
	return (1);
}

int		ft_check_commands2(t_token **tok)
{
	int	i;
	int a;

	a = 0;
	if (!(*tok))
		return (0);
	i = (*tok)->lan;
	if (!(*tok)->ncom)
		return (0);
	(*tok = (*tok)->next) ? 0 : leave();
	if (!(*tok)->comment || i != (*tok)->lan || !check_com_l((*tok)->comment))
		return (0);
	(*tok = (*tok)->next) ? 0 : leave();
	a = (*tok)->lan;
	if (i == a)
		return (0);
	if (!(*tok)->name)
		return (0);
	(*tok = (*tok)->next) ? 0 : leave();
	if (!(*tok)->comment || a != (*tok)->lan || !check_name_l((*tok)->comment))
		return (0);
	(*tok = (*tok)->next) ? 0 : leave();
	return (1);
}

int		ft_check_commands(t_token **tok)
{
	int	i;
	int a;

	a = 0;
	if (!(*tok))
		return (0);
	i = (*tok)->lan;
	if (!(*tok)->name)
		return (0);
	(*tok = (*tok)->next) ? 0 : leave();
	if (!(*tok)->comment || i != (*tok)->lan || !check_name_l((*tok)->comment))
		return (0);
	(*tok = (*tok)->next) ? 0 : leave();
	a = (*tok)->lan;
	if (i == a)
		return (0);
	if (!(*tok)->ncom)
		return (0);
	(*tok = (*tok)->next) ? 0 : leave();
	if (!(*tok)->comment || a != (*tok)->lan || !check_com_l((*tok)->comment))
		return (0);
	(*tok = (*tok)->next) ? 0 : leave();
	return (1);
}

int		ft_check(t_token *tok, t_list *sep)
{
	if (!ft_check_commands(&tok) && !ft_check_commands2(&tok))
	{
		if (tok && !tok->inst)
			ft_printf("Syntax error at token [TOKEN][%d:%d] STRING\"%s\"\n",
				tok->lan, tok->col, tok->comment);
		ft_puterror(tok, 0, tok->lan, tok);
		clean();
		return (0);
	}
	return (ft_check_every(tok, sep));
}
