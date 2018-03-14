/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 15:14:48 by nolivier          #+#    #+#             */
/*   Updated: 2017/09/28 11:07:28 by nolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		ft_check_options_third(char **argv, int *i, t_settings *sets)
{
	if (!ft_strcmp(*(argv + *i), "-ncurses"))
	{
		sets->options = (sets->options & 0x0) | NCURSES;
		while (*(argv + *i + 1) &&
		!((sets->options & NCURSES_S) && (sets->options & NCURSES_SOUND)))
		{
			*i += 1;
			if (*(argv + *i) && !(sets->options & NCURSES_S) &&
			!ft_strcmp(*(argv + *i), "--stealth"))
				sets->options |= NCURSES_S;
			else if (*(argv + *i) && !(sets->options & NCURSES_SOUND) &&
			!ft_strcmp(*(argv + *i), "--sound"))
				sets->options |= NCURSES_SOUND;
			else
				return (0);
		}
		return (1);
	}
	return (0);
}

static int		ft_check_options_second(char **argv, int *i, t_settings *sets)
{
	int				val;

	if (!ft_strcmp(*(argv + *i), "-a"))
	{
		sets->options |= AFF_OUTPUT;
		return (1);
	}
	else if (!ft_strcmp(*(argv + *i), "-v"))
	{
		*i += 1;
		if (*(argv + *i) && (val = ft_atoi(*(argv + *i))) > 0)
			sets->options |= VERBOSITY + (val & 0x1f);
		return (1);
	}
	else
		return (ft_check_options_third(argv, i, sets));
}

int				ft_check_options(char **argv, int *i, t_settings *sets)
{
	if (!ft_strcmp(*(argv + *i), "-dump") || !ft_strcmp(*(argv + *i), "-d"))
	{
		*i += 1;
		if (*(argv + *i) && (sets->memory_cycles = ft_atoi(*(argv + *i))) > 0)
			sets->options |= MEMORY_DUMP;
		return (1);
	}
	else if (!ft_strcmp(*(argv + *i), "-s"))
	{
		*i += 1;
		if (*(argv + *i) && (sets->repeat_cycles = ft_atoi(*(argv + *i))) > 0)
			sets->options |= REPEAT_DUMP;
		return (1);
	}
	else
		return (ft_check_options_second(argv, i, sets));
}
