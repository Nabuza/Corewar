/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 19:23:44 by adenis            #+#    #+#             */
/*   Updated: 2017/11/14 17:53:52 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msa.h"

void		get_name(char **s, t_oct **lst)
{
	int			i;
	t_oct		*tmp;
	char		*s2;

	if (!(*lst) || !(*s))
		ft_error("error");
	tmp = *lst;
	i = 0;
	s2 = *s;
	while (i < PROG_NAME_LENGTH + 1 && tmp)
	{
		s2[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}
	tmp = jump(tmp, 3);
	*lst = tmp;
}

void		get_comment(char **s, t_oct **lst)
{
	int			i;
	t_oct		*tmp;
	char		*s2;

	if (!(*lst) || !(*s))
		ft_error("error");
	i = 0;
	tmp = *lst;
	s2 = *s;
	while (i < COMMENT_LENGTH + 1 && tmp)
	{
		s2[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}
	tmp = jump(tmp, 3);
	*lst = tmp;
}

int			get_prog_size(t_oct **lst)
{
	int			res;
	t_oct		*tmp;

	res = 0;
	tmp = *lst;
	res = tmp ? tmp->content >> 24 : 0;
	tmp = tmp->next;
	res = tmp ? tmp->content >> 16 | res : 0;
	tmp = tmp->next;
	res = tmp ? tmp->content >> 8 | res : 0;
	tmp = tmp->next;
	res = tmp ? tmp->content | res : 0;
	tmp = tmp->next;
	*lst = tmp;
	return (res);
}

void		format_name(char **s)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin("\"", *s);
	tmp2 = ft_strjoin(tmp, "\"");
	*s ? free(*s) : 0;
	tmp ? ft_strdel(&tmp) : 0;
	*s = tmp2;
}

void		get_header(t_oct **lst)
{
	char	*name;
	char	*comment;

	name = ft_strnew(PROG_NAME_LENGTH);
	comment = ft_strnew(COMMENT_LENGTH);
	get_name(&name, lst);
	get_prog_size(lst);
	get_comment(&comment, lst);
	format_name(&name);
	format_name(&comment);
	write_output(".name ", 0, NULL);
	write_output(name, 0, "\n");
	write_output(".comment ", 0, NULL);
	write_output(comment, 0, "\n");
	name ? ft_strdel(&name) : 0;
	comment ? ft_strdel(&comment) : 0;
}
