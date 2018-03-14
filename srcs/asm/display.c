/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 16:35:23 by adenis            #+#    #+#             */
/*   Updated: 2017/11/22 11:57:59 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	printop(int val, int size)
{
	int		dif;

	dif = 0;
	if (size > 4)
		dif = size - 4;
	if (size == 4)
		ft_putchar_fd((val >> 24), FD);
	if (size >= 3)
		ft_putchar_fd((val >> 16), FD);
	if (size >= 2)
		ft_putchar_fd((val >> 8), FD);
	if (size >= 1)
		ft_putchar_fd(val, FD);
	while (dif)
	{
		ft_putchar_fd(0, FD);
		dif--;
	}
}

void	print_val(void)
{
	t_output	*pop;

	pop = OUT;
	while (pop)
	{
		if (pop->type == 2 || pop->type == 7)
		{
			pop = pop->next;
			continue ;
		}
		printop(pop->val, pop->size);
		pop = pop->next;
	}
}

void	print_name(t_header **header, char *s)
{
	int		i;

	i = 0;
	while (s[i] && i < PROG_NAME_LENGTH)
	{
		(*header)->prog_name[i] = s[i];
		i++;
	}
}

void	print_comment(t_header **header, char *s)
{
	int		i;

	i = 0;
	while (s[i] && i < COMMENT_LENGTH)
	{
		(*header)->comment[i] = s[i];
		i++;
	}
}

void	print_header(void)
{
	t_output	*tmp;
	t_header	*header;
	int			h;

	h = 0;
	header = (t_header *)malloc(sizeof(t_header));
	ft_bzero(header->prog_name, PROG_NAME_LENGTH);
	ft_bzero(header->comment, COMMENT_LENGTH);
	header->magic = magic_n_size(COREWAR_EXEC_MAGIC);
	header->prog_size = magic_n_size(PROG_SIZE);
	tmp = OUT;
	while (tmp)
	{
		if (tmp->type == 8)
		{
			if (tmp->next && ft_strstr(tmp->name, NAME_CMD_STRING))
				print_name(&header, (char *)tmp->next->name);
			if (tmp->next && ft_strstr(tmp->name, COMMENT_CMD_STRING))
				print_comment(&header, (char *)tmp->next->name);
		}
		tmp = tmp->next;
	}
	write(FD, header, sizeof(t_header));
	header ? free(header) : 0;
}
