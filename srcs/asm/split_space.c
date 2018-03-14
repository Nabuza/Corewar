/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 16:39:17 by nagaloul          #+#    #+#             */
/*   Updated: 2017/10/30 13:47:44 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"
#include "op.h"

int		count_l(char *str)
{
	int j;
	int i;

	i = 0;
	j = 0;
	while (str[i])
	{
		while ((str[i]) && (str[i] == ' ' || str[i] == '\t'))
			i++;
		while ((str[i]) && str[i] != ' ' && str[i] != '\t')
		{
			j++;
			i++;
		}
		return (j);
	}
	return (j);
}

void	filltab(char *tab, char *str)
{
	int i;
	int a;

	a = 0;
	i = 0;
	while ((str[i]) && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while ((str[i]) && str[i] != ' ' && str[i] != '\t')
	{
		tab[a] = str[i];
		a++;
		i++;
	}
	tab[a] = '\0';
}

void	counttab(char **tab, char *str)
{
	int i;
	int	a;

	a = 0;
	i = 0;
	while (str[i])
	{
		if (!(tab[a] = malloc(sizeof(char) * count_l(&str[i]) + 1)))
			return ;
		filltab(tab[a], &str[i]);
		while ((str[i]) && (str[i] == ' ' || str[i] == '\t'))
			i++;
		while ((str[i]) && (str[i] != '\t' && str[i] != ' '))
			i++;
		while ((str[i]) && (str[i] == ' ' || str[i] == '\t'))
			i++;
		a++;
	}
}

int		count_w(char *str)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (str[i])
	{
		while ((str[i]) && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i] == '\0')
			return (j);
		j++;
		while ((str[i]) && str[i] != ' ' && str[i] != '\t')
			i++;
		if (str[i] == '\0')
			return (j);
		i++;
	}
	return (j);
}

char	**split_space(char *str)
{
	char	**tab;
	int		b;

	b = count_w(str);
	if (!(tab = (char**)malloc(sizeof(char*) * b + 1)))
		return (NULL);
	tab[b] = 0;
	if (b == 0)
		return (tab);
	counttab(tab, str);
	return (tab);
}
