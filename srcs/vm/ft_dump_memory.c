/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dump_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 15:14:48 by nolivier          #+#    #+#             */
/*   Updated: 2017/09/25 13:06:09 by nolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static char			*ft_fill_hex(char *addr, int nb)
{
	char			*b;
	int				i;

	b = "0123456789abcdef";
	i = 0;
	while (i < 4)
	{
		addr[3 - i] = b[nb % 16];
		nb = nb / 16;
		i++;
	}
	addr[4] = '\0';
	return (addr);
}

void				ft_dump_memory(unsigned char *memory, int size)
{
	char			addr[5];
	char			*b;
	int				i;
	int				j;

	if (LINE_SIZE < 1)
		return ;
	b = "0123456789abcdef";
	i = 0;
	while (i < size)
	{
		ft_printf("0x%s :", ft_fill_hex(addr, i));
		j = 0;
		while (j < LINE_SIZE && i + j < size)
		{
			ft_printf(" %c%c", b[memory[i + j] / 16], b[memory[i + j] % 16]);
			j++;
		}
		i += LINE_SIZE;
		write(1, " \n", 2);
	}
}
