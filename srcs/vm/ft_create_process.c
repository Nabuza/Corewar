/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 13:32:42 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/14 10:56:52 by nolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			ft_create_process(t_process **begin, t_process *father,
	unsigned char *index, t_settings *sets)
{
	t_process		*son;

	if (!(son = (t_process *)malloc(sizeof(t_process))))
	{
		ft_dprintf(2, "ft_create_process: malloc error\n");
		return (0);
	}
	ft_memcpy(son, father, sizeof(t_process));
	son->proc_counter = index - sets->memory;
	son->num = sets->process_num++;
	sets->processes++;
	son->next = *begin;
	*begin = son;
	return (1);
}
