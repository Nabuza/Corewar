/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaloul <nagaloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 14:44:10 by nagaloul          #+#    #+#             */
/*   Updated: 2017/11/22 15:46:58 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"
#include "op.h"

int		ft_sep(char *str)
{
	int	i;

	i = 0;
	while ((str[i]) && str[i] != ' ' && str[i] != '\t')
	{
		if (str[i] == ';' || str[i] == COMMENT_CHAR)
			break ;
		if (i > 0 && str[i] == LABEL_CHAR && str[i - 1]
				!= DIRECT_CHAR && str[i - 1] != SEPARATOR_CHAR)
		{
			i++;
			break ;
		}
		if (i > 0 && str[i] == SEPARATOR_CHAR)
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

void	ft_try(t_token **tok, char *str, int *count, int b)
{
	int		i;
	char	temp[3];

	temp[1] = SEPARATOR_CHAR;
	temp[2] = '\0';
	i = ft_sep(str);
	temp[0] = str[i];
	str[i] = '\0';
	if (ft_strcmp(str, &temp[1]))
		ft_push_token(tok, str, *count + 1, b);
	str[i] = temp[0];
	if (str[i - 1] == LABEL_CHAR || str[i - 1] == SEPARATOR_CHAR)
		i--;
	*count = *count + i;
}

int		only(char *str)
{
	int i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == SEPARATOR_CHAR)
		return (0);
	return (1);
}

void	split_tok(t_token **tok, char *str, int b)
{
	int		i;
	char	tab[2];

	i = 0;
	tab[0] = SEPARATOR_CHAR;
	tab[1] = 0;
	if (!only(str))
		ft_push_token(tok, tab, 1, b);
	else
		while (str[i])
		{
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (str[i] == '\0' || str[i] == COMMENT_CHAR || str[i] == ';')
				break ;
			ft_try(tok, &str[i], &i, b);
			if (str[i] == ';' || str[i] == COMMENT_CHAR)
				break ;
			if (str[i] != '\0')
				i++;
		}
}
