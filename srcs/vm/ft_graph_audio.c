/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_audio.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:54:37 by khabbar           #+#    #+#             */
/*   Updated: 2017/11/22 12:42:45 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		ft_play_sound(char *sound, int wait)
{
	pid_t		father;
	char		*options[3];

	options[0] = ft_strdup("afplay");
	options[1] = ft_strdup(sound);
	options[2] = 0;
	if (wait)
		waitpid(-1, NULL, 0);
	if ((father = fork()) == 0)
		execve("/usr/bin/afplay", options, NULL);
	ft_strdel(&options[0]);
	ft_strdel(&options[1]);
}

void			ft_graph_end_audio(t_settings *sets)
{
	if (!(sets->options & NCURSES_SOUND))
		return ;
	if (!(sets->status & GAME_CANCELED) && (sets->status & GAME_ENDED))
		ft_play_sound("srcs/sound/Game_Over.mp3", 1);
}

void			ft_graph_audio(t_settings *sets)
{
	if (!(sets->options & NCURSES_SOUND))
		return ;
	if (sets->deaths_proc == 0)
		return ;
	if (sets->deaths_proc == 1)
		ft_play_sound("srcs/sound/Headshoot.mp3", 0);
	else if (sets->deaths_proc == 2)
		ft_play_sound("srcs/sound/Double_kill.mp3", 0);
	else if (sets->deaths_proc == 3)
		ft_play_sound("srcs/sound/Triple_kill.mp3", 0);
	else if (sets->deaths_proc < 10)
		ft_play_sound("srcs/sound/Multi_kill.mp3", 0);
	else if (sets->deaths_proc < 20)
		ft_play_sound("srcs/sound/Ultra_kill.mp3", 0);
	else if (sets->deaths_proc < 30)
		ft_play_sound("srcs/sound/Monster_kill.mp3", 0);
	else if (sets->deaths_proc < 60)
		ft_play_sound("srcs/sound/Rampage.mp3", 0);
	else if (sets->deaths_proc >= 60)
		ft_play_sound("srcs/sound/Holy_shit.mp3", 0);
}
