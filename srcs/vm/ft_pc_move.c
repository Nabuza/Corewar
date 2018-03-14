/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pc_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 13:17:41 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/28 11:25:52 by nolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		ft_display_mem(unsigned char *memory, unsigned int proc_counter,
	unsigned int counter)
{
	char			*base;
	unsigned int	i;

	base = "0123456789abcdef";
	i = 0;
	while (i < counter)
	{
		ft_printf(" %c%c", base[memory[(proc_counter + i) % MEM_SIZE] / 16],
		base[memory[(proc_counter + i) % MEM_SIZE] % 16]);
		i += 1;
	}
	write(1, " \n", 2);
}

static char		*ft_fill_hex(char *addr, int nb)
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

void			ft_print_pc_move(t_process *process,
	t_settings *sets, unsigned int counter)
{
	char			addr1[5];
	char			addr2[5];

	if ((sets->options & VERBOSITY) && (sets->options & PC_MOVEMENTS))
	{
		ft_printf("ADV %d (0x%s -> 0x%s)", counter,
		ft_fill_hex(addr1, process->proc_counter),
		ft_fill_hex(addr2, process->proc_counter + counter));
		ft_display_mem(sets->memory, process->proc_counter, counter);
	}
}

void			ft_pc_move(t_process *process,
	t_settings *sets, unsigned int counter)
{
	ft_print_pc_move(process, sets, counter);
	process->cycle_count = 0;
	process->proc_counter = (process->proc_counter + counter) % MEM_SIZE;
}
