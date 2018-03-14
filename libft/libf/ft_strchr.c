/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 19:04:00 by khabbar           #+#    #+#             */
/*   Updated: 2017/08/03 19:04:02 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

char	*ft_strchr(const char *s, int c)
{
	if (s == NULL || *s == '\0')
		return (NULL);
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return (char*)(&(*s));
	return (NULL);
}
