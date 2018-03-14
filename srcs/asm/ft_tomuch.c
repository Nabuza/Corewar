/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tomuch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaloul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 13:47:07 by nagaloul          #+#    #+#             */
/*   Updated: 2017/10/22 13:08:54 by nagaloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		ft_tomuch(t_token *tok, int i)
{
	if (tok->next && tok->next->lan == i)
	{
		ft_puterror(tok->next, 0, i, tok);
		return (0);
	}
	return (1);
}
