/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 13:08:20 by khabbar           #+#    #+#             */
/*   Updated: 2017/02/20 13:57:46 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

int		ft_isalnum(int c)
{
	if (ft_isdigit(c) == 1 || ft_isalpha(c) == 1)
		return (1);
	else
		return (0);
}
