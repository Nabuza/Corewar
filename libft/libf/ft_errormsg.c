/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 20:40:50 by khabbar           #+#    #+#             */
/*   Updated: 2017/08/03 20:41:07 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

void	ft_errormsg(char *env, char *cmd, char *str)
{
	if (env)
		ft_putstr_fd(env, 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	if (str)
		ft_putendl_fd(str, 2);
}
