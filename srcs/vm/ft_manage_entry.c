/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_entry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 15:14:48 by nolivier          #+#    #+#             */
/*   Updated: 2017/09/28 11:28:05 by nolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int			ft_add_specify_entry(int *player_number, int *i,
		int *nb_champ, int val)
{
	int				tmp;
	int				j;

	if (player_number[val - 1] == 0)
	{
		player_number[val - 1] = *i + 1;
		*nb_champ += 1;
	}
	else
	{
		tmp = player_number[val - 1];
		j = val - 1;
		while (player_number[j] && j <= MAX_ARGS_NUMBER)
			j++;
		if (j <= MAX_ARGS_NUMBER && player_number[j] == 0)
		{
			player_number[val - 1] = *i + 1;
			player_number[j] = tmp;
			*nb_champ += 1;
		}
		else
			return (ft_error("Bad player number specification\n"));
	}
	return (1);
}

static int			ft_specify_player(char **argv, int *player_number,
		int *i, int *nb_champ)
{
	int				val;

	*i += 1;
	if (*(argv + *i) && (val = ft_atoi(*(argv + *i))) > 0)
	{
		*i += 1;
		if (*(argv + *i) && val <= MAX_ARGS_NUMBER)
		{
			if (ft_add_specify_entry(player_number, i, nb_champ, val) < 1)
				return (0);
		}
		else
			return (0);
	}
	else
		return (0);
	return (1);
}

static int			ft_add_entry(int *player_number, int i, int *nb_champ)
{
	int				j;

	j = 0;
	while (player_number[j] && j <= MAX_ARGS_NUMBER)
		j++;
	if (j <= MAX_ARGS_NUMBER)
	{
		player_number[j] = i + 1;
		*nb_champ += 1;
	}
	else
		return (ft_error("Too many champions\n"));
	return (1);
}

int					ft_manage_entry(char **argv, int *player_number,
	t_settings *sets)
{
	int				nb_champ;
	int				i;

	nb_champ = 0;
	ft_memset(player_number, 0, MAX_ARGS_NUMBER * 4);
	i = 0;
	while (*(argv + i))
	{
		if (!ft_strcmp(*(argv + i), "-n"))
		{
			if (ft_specify_player(argv, player_number, &i, &nb_champ) < 1)
				return (0);
		}
		else if (ft_check_options(argv, &i, sets) < 1)
		{
			if (ft_add_entry(player_number, i, &nb_champ) < 1)
				return (0);
		}
		i++;
	}
	if (nb_champ > MAX_PLAYERS)
		return (ft_error("Too many champions\n"));
	return (nb_champ);
}
