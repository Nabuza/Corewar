/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hard.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaloul <nagaloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 09:32:24 by nagaloul          #+#    #+#             */
/*   Updated: 2017/11/21 17:28:09 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

static int		ft_acc(char *str, t_list *line, int *b)
{
	int		i;
	int		count;
	char	*s;

	i = 0;
	while (str[i])
		i++;
	count = i;
	i = 0;
	while (line && (s = (char *)line->content))
	{
		while (s[i] && s[i] != '"')
			i++;
		count = count + i + 1;
		if (s[i] == '"')
		{
			*b = *b + 1;
			return (++count);
		}
		line = line->next;
		*b = *b + 1;
		i = 0;
	}
	*b = *b + 1;
	return (count);
}

static t_list	*ft_fill(char *str, t_list *line, char *buffer)
{
	int		i;
	int		a;
	char	*s;

	a = -1;
	i = -1;
	while (str[++i])
		buffer[++a] = str[i];
	buffer[++a] = '\n';
	i = 0;
	while (line && (s = (char *)line->content))
	{
		while (s[i] && s[i] != '"')
			buffer[++a] = s[i++];
		if (s[i] == '"')
		{
			buffer[++a] = s[i];
			break ;
		}
		(s[i] == '\0') ? (buffer[++a] = '\n') : 0;
		line = line->next;
		i = 0;
	}
	buffer[++a] = '\0';
	return (line);
}

static void		ft_quote(t_token **tok, t_list **line, int *b)
{
	int		i;
	int		a;
	char	*buff;
	char	*s;
	int		tmp;

	tmp = *b;
	buff = NULL;
	i = 0;
	a = 0;
	s = (char *)(*line)->content;
	while (s && s[i] && s[i] != '"')
		i++;
	a = ft_acc(&s[i], (*line)->next, b);
	(buff = malloc(sizeof(char) * a + 1)) ? 0 : exit(0);
	*line = ft_fill(&s[i], (*line)->next, buff);
	ft_push_token(tok, buff, i, tmp);
	buff ? free(buff) : 0;
}

void			ft_hard(t_token **tok, t_list **line, int *b)
{
	int		i;
	char	*s;

	i = 0;
	s = (*line)->content;
	while (s && s[i])
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (s[i] == ';' || s[i] == COMMENT_CHAR)
			break ;
		if (s[i] == '"')
		{
			ft_quote(tok, line, b);
			break ;
		}
		else
			ft_naco(tok, &s[i], &i, b);
		if (s[i] == ';' || s[i] == COMMENT_CHAR)
			break ;
		i++;
	}
}
