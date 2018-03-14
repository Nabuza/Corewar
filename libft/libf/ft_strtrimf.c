/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 12:25:10 by khabbar           #+#    #+#             */
/*   Updated: 2017/08/03 18:43:17 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

static char	*trim(unsigned int i, char **s, unsigned int len, char **s1)
{
	if (i == ft_strlen(*s) && len == 0)
	{
		ft_strdel(s);
		return (NULL);
	}
	else if (len >= i)
	{
		*s1 = ft_strsub(*s1, i, len - i + 1);
		ft_strdel(s);
		return (*s1);
	}
	return (NULL);
}

char		*ft_strtrimf(char *s)
{
	char			*s1;
	unsigned int	i;
	unsigned int	len;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s) - 1;
	s1 = (char*)s;
	if (s1[i] == '\0')
		return (ft_strnew(1));
	while ((s1[i] == ' ' || s1[i] == '\n' || s1[i] == '\t') && (s1[i]))
		i++;
	while ((s1[len] == ' ' || s1[len] == '\n' || s1[len] == '\t') && (len))
		len--;
	return (trim(i, &s, len, &s1));
}
