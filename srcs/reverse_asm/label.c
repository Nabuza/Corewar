/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:38:59 by adenis            #+#    #+#             */
/*   Updated: 2017/11/14 18:27:13 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msa.h"

void		lab_insert(t_list *lst)
{
	t_list	*tmp;
	char	*s1;
	char	*s2;

	s1 = ft_itoa(LAB++);
	s2 = ft_strjoin(s1, ":\n");
	if (!(tmp = ft_lstnew(NULL, 0)))
		ft_error("error");
	tmp->content = ft_strjoin("label", s2);
	tmp->content_size = lst->next->content_size;
	tmp->next = lst->next;
	lst->next = tmp;
	s1 ? ft_strdel(&s1) : 0;
	s2 ? ft_strdel(&s2) : 0;
}

void		handle_goto(t_list *lst)
{
	int		val;
	char	*s;
	t_list	*tmp;

	if (!lst)
		return ;
	val = ft_atoi(lst->content);
	if (val)
		val += lst->content_size;
	if ((tmp = check_goto(lst->content, val)))
	{
		if (tmp->next && !ft_strstr(tmp->next->content, "label"))
			lab_insert(tmp);
		lst->content ? ft_strdel((char **)&lst->content) : 0;
		if (!(s = ft_strjoin(":", tmp->next->content)))
			ft_error("error");
		s[ft_strlen(s) - 1] = ' ';
		s[ft_strlen(s) - 2] = ',';
		lst->content = s;
	}
}

void		handle_label(void)
{
	t_list	*lst;

	lst = OUT;
	while (lst)
	{
		if (ft_strchr(lst->content, DIRECT_CHAR))
			handle_goto(lst->next);
		lst = lst->next;
	}
}

void		handle_last(void)
{
	t_list	*tmp;
	char	*s;

	s = NULL;
	tmp = OUT;
	while (tmp)
	{
		s = tmp->next ? ft_strdup((char *)tmp->next->content) : NULL;
		if (s && s[0] == '#')
		{
			s ? free(s) : NULL;
			s = ft_strdup((char *)tmp->content);
			if (ft_strrchr(s, ' ') && ft_strrchr(s, ','))
			{
				ft_strrchr(s, ' ')[0] = '\0';
				ft_strrchr(s, ',')[0] = ' ';
				tmp->content ? free(tmp->content) : 0;
				tmp->content = s;
			}
		}
		else
			s ? free(s) : NULL;
		tmp = tmp->next;
	}
}
