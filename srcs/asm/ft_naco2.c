/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_naco2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaloul <nagaloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:43:39 by nagaloul          #+#    #+#             */
/*   Updated: 2017/11/17 17:02:30 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

static int	ft_sip(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t'
			&& str[i] != ';' && str[i] != COMMENT_CHAR)
		i++;
	return (i);
}

void		ft_naco2(t_token **tok, char *str, int *b)
{
	int		i;
	char	temp;
	int		tmp;

	i = 0;
	while (str[i] && str[i] != '"')
		i++;
	i++;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] != '\0' && str[i] != ';' && str[i] != COMMENT_CHAR)
	{
		tmp = i;
		i = ft_sip(&str[tmp]) + tmp;
		temp = str[i];
		str[i] = '\0';
		ft_push_token(tok, &str[tmp], tmp, *b);
		str[i] = temp;
	}
}
