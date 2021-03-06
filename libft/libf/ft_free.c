/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 15:57:35 by khabbar           #+#    #+#             */
/*   Updated: 2017/07/13 13:51:44 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

int		ft_free(char **tab, char **line, int w)
{
	int			i;

	i = -1;
	if ((w == 2 || w == 3) && *line)
		ft_strdel(line);
	if ((w == 1 || w == 3) && tab)
	{
		while (tab[++i])
			tab[i] ? ft_strdel(&tab[i]) : 0;
		free(tab);
	}
	return (1);
}
