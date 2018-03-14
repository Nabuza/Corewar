/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolivier <nolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 12:59:34 by nolivier          #+#    #+#             */
/*   Updated: 2017/11/12 17:08:35 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <ncurses.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/time.h>
# include <time.h>
# include <math.h>

# include "op.h"
# include "../libft/inc/libftprintf.h"

# define COLOR_P1		COLOR_MAGENTA
# define COLOR_P2		COLOR_YELLOW
# define COLOR_P3		COLOR_BLUE
# define COLOR_P4		COLOR_RED

# define STORE_TIME		50
# define LIVE_TIME		50
# define INIT_SPEED		50
# define MIN_SPEED		1
# define MAX_SPEED		1000

# define LINE_SIZE			32 * 2
# define HEADER_SIZE		sizeof(t_header)

# define AFF_OUTPUT			0x20
# define MEMORY_DUMP		0x40
# define REPEAT_DUMP		0x80
# define VERBOSITY			0x100
# define BINARY				0x200
# define BINARY_STEALTH		0x400
# define NCURSES			0x800
# define NCURSES_S			0x1000
# define NCURSES_SOUND      0x2000
# define LIVES				0x1
# define CYCLES				0x2
# define OPERATIONS			0x4
# define DEATHS				0x8
# define PC_MOVEMENTS		0x10

# define GAME_ENDED			0x1
# define GAME_CANCELED		0x2
# define PAUSE				0x4
# define START				0x8

typedef struct	s_lives
{
	unsigned int			last_live;
	unsigned int			current_period;
	unsigned int			last_period;
}				t_lives;

typedef struct	s_settings
{
	unsigned char			*info_mem;
	unsigned char			*memory;
	t_header				*champs;
	unsigned int			total_lives;
	t_lives					*lives;
	unsigned int			nb_champs;
	unsigned int			process_num;
	unsigned int			processes;
	unsigned int			deaths_proc;
	unsigned int			options;
	int						memory_cycles;
	int						repeat_cycles;
	unsigned int			cycle_to_die;
	unsigned int			cycle;
	unsigned int			status;
	unsigned int			start_period;
	unsigned int			checks;
	unsigned int			last_dump;
	struct timespec			time;
	int						speed_limit;
	long					cycle_time;
}				t_settings;

# define LIVE				0x1
# define CARRY				0x2

typedef struct	s_process
{
	unsigned int			status;
	unsigned int			num;
	unsigned int			proc_counter;
	unsigned int			cycle_count;
	unsigned int			last_live;
	unsigned char			registers[REG_NUMBER * REG_SIZE];
	struct s_process		*next;
}				t_process;

typedef struct	s_window
{
	WINDOW		*mem;
	WINDOW		*info;
	int			x;
	int			y;
}				t_window;

void			ft_init_graph(t_settings *sets);
void			ft_unset_graph(t_settings *sets);
void			ft_graph(t_settings *sets, t_window *win);
void			ft_graph_dump(t_window *win, t_settings *sets);
void			ft_graph_info(t_window *win, t_settings *sets);
void			ft_live_breakdown(t_window *win, t_settings *sets, char *msg,
		int mod);
void			ft_graph_time(t_settings *sets);
void			ft_graph_winner(t_window *win, t_settings *sets);
void			ft_graph_process(t_process *process, t_settings *sets);
void			ft_graph_audio(t_settings *sets);
void			ft_graph_end_audio(t_settings *sets);
void			ft_press_to_dump(t_settings *sets, SCREEN **scr);
void			ft_check_ctd(t_settings *sets, t_process **process);
int				ft_run_kitty_run(t_settings *sets, t_window *win);
int				ft_error(char *str);
void			ft_print_winner(t_settings *sets, t_window *win);
void			ft_dump_memory(unsigned char *memory, int size);
int				ft_invert_endian(int nb);
int				ft_check_options(char **argv, int *i, t_settings *sets);
int				ft_manage_entry(char **argv, int *player_number,
		t_settings *sets);
int				ft_load(char **argv, t_settings *sets);
t_process		*ft_init_process(t_settings *sets);
unsigned char	ft_get_ocp(t_settings *sets, t_process *process,
		unsigned int *counter, unsigned char **params);
unsigned char	*ft_get_add(unsigned char *memory, t_process *process,
		unsigned int counter, unsigned int param_num);
int				ft_get_val(t_process *process, unsigned char *addr,
		unsigned char *memory, unsigned int param);
void			ft_modif_carry_reg(t_process *process,
		unsigned char *reg, int op_code);
void			ft_print_pc_move(t_process *process,
		t_settings *sets, unsigned int counter);
void			ft_pc_move(t_process *process,
		t_settings *sets, unsigned int counter);
int				ft_create_process(t_process **begin, t_process *father,
		unsigned char *index, t_settings *sets);
int				ft_live(t_settings *sets,
		t_process *process, t_process **begin);
int				ft_ld(t_settings *sets,
		t_process *process, t_process **begin);
int				ft_st(t_settings *sets,
		t_process *process, t_process **begin);
int				ft_add(t_settings *sets,
		t_process *process, t_process **begin);
int				ft_sub(t_settings *sets,
		t_process *process, t_process **begin);
int				ft_and(t_settings *sets,
		t_process *process, t_process **begin);
int				ft_or(t_settings *sets,
		t_process *process, t_process **begin);
int				ft_xor(t_settings *sets,
		t_process *process, t_process **begin);
int				ft_zjmp(t_settings *sets,
		t_process *process, t_process **begin);
int				ft_ldi(t_settings *sets,
		t_process *process, t_process **begin);
int				ft_sti(t_settings *sets,
		t_process *process, t_process **begin);
int				ft_fork(t_settings *sets,
		t_process *process, t_process **begin);
int				ft_lld(t_settings *sets,
		t_process *process, t_process **begin);
int				ft_lldi(t_settings *sets,
		t_process *process, t_process **begin);
int				ft_lfork(t_settings *sets,
		t_process *process, t_process **begin);
int				ft_aff(t_settings *sets,
		t_process *process, t_process **begin);

typedef struct	s_op_fct
{
	int					(*ptr)(t_settings *sets,
			t_process *process, t_process **begin);
	unsigned int		op_code;
	unsigned int		add_restrict;
	unsigned int		modif_carry;
}				t_op_fct;

static			t_op_fct g_fct_tab[17] =
{
	{&ft_live, 1, 1, 0},
	{&ft_ld, 2, 1, 1},
	{&ft_st, 3, 1, 0},
	{&ft_add, 4, 1, 1},
	{&ft_sub, 5, 1, 1},
	{&ft_and, 6, 1, 1},
	{&ft_or, 7, 1, 1},
	{&ft_xor, 8, 1, 1},
	{&ft_zjmp, 9, 1, 0},
	{&ft_ldi, 10, 1, 0},
	{&ft_sti, 11, 1, 0},
	{&ft_fork, 12, 1, 0},
	{&ft_lld, 13, 0, 1},
	{&ft_lldi, 14, 0, 1},
	{&ft_lfork, 15, 0, 0},
	{&ft_aff, 16, 1, 0},
	{0, 0, 0, 0}
};

#endif
