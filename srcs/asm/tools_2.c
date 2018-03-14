/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 19:58:23 by adenis            #+#    #+#             */
/*   Updated: 2017/11/21 15:34:57 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

char		*getattribute(t_token *tok)
{
	if (tok->reg)
		return (tok->reg);
	else if (tok->lab)
		return (tok->lab);
	else if (tok->comment)
		return (tok->comment);
	else if (tok->dirlab)
		return (tok->dirlab);
	else if (tok->indirlab)
		return (tok->indirlab);
	else if (tok->dir)
		return (tok->dir);
	else if (tok->name)
		return (tok->name);
	else if (tok->ncom)
		return (tok->ncom);
	else if (tok->indir)
		return (tok->indir);
	return (tok->unknow);
}

void		read_check(int fd, t_list *ops)
{
	char	buff;
	char	tmp;

	while (read(fd, &buff, 1) != 0)
		tmp = buff;
	if (tmp == '\n')
		return ;
	while (ops && ops->next)
		ops = ops->next;
	close(fd);
	if (!ft_lastline((char *)ops->content))
	{
		ft_printf("parse error, file must end by a newline\n");
		clean();
	}
}

void		get_ops(t_list **ops, int fd)
{
	char		*line;

	line = NULL;
	*ops = NULL;
	while (get_next_line(fd, &line))
	{
		ft_push_back(ops, line);
		ft_strdel(&line);
	}
	if (!*ops)
		clean();
}
