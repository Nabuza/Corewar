/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 13:36:32 by khabbar           #+#    #+#             */
/*   Updated: 2017/08/15 13:36:35 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

void	ft_precision(char *str, t_flags *flags)
{
	long int	i;

	i = -1;
	if (ft_strchr(str, '.'))
	{
		while (str[++i])
			if (str[i] == '.')
			{
				flags->pr = ft_atoi(&str[i + 1]);
				flags->isp = 1;
				break ;
			}
	}
}
