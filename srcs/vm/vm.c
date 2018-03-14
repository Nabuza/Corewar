/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolivier <nolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 15:14:48 by nolivier          #+#    #+#             */
/*   Updated: 2017/11/22 11:28:43 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			ft_print_intro(t_settings *sets)
{
	unsigned int		i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < sets->nb_champs)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		i + 1, (sets->champs + i)->prog_size, (sets->champs + i)->prog_name,
		(sets->champs + i)->comment);
		i++;
	}
}

static int			ft_usage(void)
{
	ft_printf("Usage: ./corewar [-d N -s N -v N | -ncurse --stealth --sound] "
	"[-a] | -n N <champion1.cor> <...>\n"
	"\t-a        : Prints output from \"aff\" (Default is to hide it)\n"
	"#### TEXT OUTPUT MODE ####################################################"
	"######\n""\t-d N      : Dumps memory after N cycles then exits\n"
	"\t-s N      : Runs N cycles, dumps memory, pauses, then repeats\n"
	"\t-v N      : Verbosity levels, can be added together to enable several\n"
	"\t\t- 0 : Show only essentials\n"
	"\t\t- 1 : Show lives\n"
	"\t\t- 2 : Show cycles\n"
	"\t\t- 4 : Show operations (Params are NOT litteral ...)\n"
	"\t\t- 8 : Show deaths\n"
	"\t\t- 16 : Show PC movements (Except for jumps)\n"
	"#### NCURSES OUTPUT MODE #################################################"
	"######\n""\t-ncurses        : Ncurses output mode\n"
	"\t--stealth : Hides the real contents of the memory\n"
	"\t--sound : Play sound when processes die and game end\n"
	"##########################################################################"
	"######\n");
	return (0);
}

static int			ft_free_err(t_settings *sets)
{
	free(sets->champs);
	free(sets->lives);
	free(sets->memory);
	return (1);
}

static int			ft_corewar(char **argv)
{
	t_settings		sets;
	t_window		win;

	if (!(sets.memory = (unsigned char*)malloc(sizeof(unsigned char) *
		MEM_SIZE)))
		return (0);
	if (!(sets.nb_champs = ft_load(argv + 1, &sets)))
	{
		free(sets.memory);
		return (ft_error("Can t load champions!\n"));
	}
	sets.status = 0;
	if (!(sets.options & NCURSES))
		ft_print_intro(&sets);
	else
	{
		if (!(sets.info_mem = (unsigned char *)malloc(sizeof(unsigned char) *
		3 * MEM_SIZE)))
			return (ft_free_err(&sets));
		sets.options &= ~VERBOSITY;
		sets.status |= (PAUSE | START);
	}
	ft_init_graph(&sets);
	ft_run_kitty_run(&sets, &win);
	return (ft_free_err(&sets));
}

int					main(int argc, char **argv)
{
	if (argc < 2)
		return (ft_usage());
	ft_corewar(argv);
	return (1);
}
