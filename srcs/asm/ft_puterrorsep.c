/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterrorsep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaloul <nagaloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 16:09:31 by nagaloul          #+#    #+#             */
/*   Updated: 2017/11/17 17:03:32 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	ft_puterrorsep(int i)
{
	if (i < 10)
		ft_printf("Syntax error at token [TOKEN][00%i] SEPARATOR \",\"\n", i);
	else if (i < 100)
		ft_printf("Syntax error at token [TOKEN][0%i] SEPARATOR \",\"\n", i);
	else
		ft_printf("Syntax error at token [TOKEN][%i] SEPARATOR \",\"\n", i);
}
