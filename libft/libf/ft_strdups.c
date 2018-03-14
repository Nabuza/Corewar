/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdups.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 10:07:04 by khabbar           #+#    #+#             */
/*   Updated: 2017/08/03 18:29:51 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

char	*ft_strdups(char *src, char **dest)
{
	if (!(*src))
		return (NULL);
	ft_strdel(dest);
	if (!((*dest) = (char *)malloc(sizeof(char) * (ft_strlen(src)))))
		return (NULL);
	ft_strcpy(*dest, src);
	return (*dest);
}
