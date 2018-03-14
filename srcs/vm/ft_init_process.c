/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 15:14:48 by nolivier          #+#    #+#             */
/*   Updated: 2017/09/25 13:06:09 by nolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			ft_write_id_register(unsigned char *reg, unsigned int nb)
{
	int				i;

	i = 0;
	while (i < REG_SIZE)
	{
		reg[REG_SIZE - 1 - i] = (unsigned char)
			((nb >> (i * 8)) ^ 0xff);
		i++;
	}
}

static int			ft_init_settings(t_settings *sets)
{
	sets->cycle_to_die = CYCLE_TO_DIE;
	sets->process_num = 1;
	sets->processes = sets->nb_champs;
	sets->total_lives = 0;
	sets->start_period = 0;
	sets->checks = 0;
	if (!(sets->lives = (t_lives*)malloc(sizeof(t_lives) * sets->nb_champs)))
		return (0);
	ft_memset(sets->lives, 0, sizeof(t_lives) * sets->nb_champs);
	return (1);
}

static t_process	*ft_free_error(t_settings *sets, t_process *process)
{
	t_process		*tmp;

	while (process)
	{
		tmp = process->next;
		free(process);
		process = tmp;
	}
	free(sets->champs);
	free(sets->lives);
	return (0);
}

t_process			*ft_init_process(t_settings *sets)
{
	t_process		*process;
	t_process		*tmp;
	unsigned int	i;

	if (!(ft_init_settings(sets)))
		return (0);
	i = 0;
	process = NULL;
	while (i < sets->nb_champs)
	{
		if (!(tmp = (t_process*)malloc(sizeof(t_process))))
			return (ft_free_error(sets, process));
		tmp->next = (!process) ? NULL : process;
		process = tmp;
		process->status = ((i + 1) << (3 * 8)) & 0xff000000;
		process->num = sets->process_num++;
		process->proc_counter = i * (MEM_SIZE / sets->nb_champs);
		process->cycle_count = 0;
		process->last_live = 0;
		ft_memset(process->registers, 0, REG_NUMBER * REG_SIZE);
		ft_write_id_register(process->registers, i);
		i++;
	}
	return (process);
}
