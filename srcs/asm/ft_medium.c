/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_medium.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaloul <nagaloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:43:39 by nagaloul          #+#    #+#             */
/*   Updated: 2017/11/19 17:03:53 by nagaloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

static void	ft_quotes(t_token **tok, char *str, int *count, int *b)
{
	int		i;
	char	temp;

	i = 1;
	while (str[i] && str[i] != '"')
		i++;
	temp = str[i + 1];
	str[i + 1] = '\0';
	ft_push_token(tok, str, *count + 1, *b);
	str[i + 1] = temp;
	*count = *count + i;
}

void		ft_medium(t_token **tok, char *str, int *a)
{
	int		i;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == ';' || str[i] == COMMENT_CHAR)
			break ;
		if (str[i] == '"')
			ft_quotes(tok, &str[i], &i, a);
		else
			ft_naco(tok, &str[i], &i, a);
		if (str[i] == ';' || str[i] == COMMENT_CHAR)
			break ;
		i++;
	}
}
