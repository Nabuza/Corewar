/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolivier <nolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 15:14:48 by nolivier          #+#    #+#             */
/*   Updated: 2017/11/22 12:37:56 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int			ft_extract_header(int fd, t_header *champs)
{
	int				ret;
	char			buf[HEADER_SIZE];

	if ((ret = read(fd, buf, HEADER_SIZE)) < (int)HEADER_SIZE)
		return (0);
	ft_memcpy(champs, buf, HEADER_SIZE);
	champs->magic = ft_invert_endian(champs->magic);
	champs->prog_size = ft_invert_endian(champs->prog_size);
	if (champs->magic != COREWAR_EXEC_MAGIC)
		return (ft_error("Wrong Magic number!!!\n"));
	return (1);
}

static int			ft_extract_prog(int fd, t_header *champs,
	unsigned char *memory)
{
	int				ret;
	char			buf[CHAMP_MAX_SIZE + 1];

	if ((ret = read(fd, buf, CHAMP_MAX_SIZE + 1)) < 1)
		return (0);
	if (ret > CHAMP_MAX_SIZE)
		return (ft_error("Champion too big!\n"));
	if ((unsigned int)ret != champs->prog_size)
	{
		ft_printf("The size shown differs from the size of the program!\n"
		"Champ Size: %d bytes\nSize program: %d bytes\n",
		ret, champs->prog_size);
		champs->prog_size = ret;
	}
	ft_memcpy(memory, buf, ret);
	return (1);
}

static t_header		*ft_free_error(t_header *champs)
{
	free(champs);
	return (0);
}

static t_header		*ft_insert_champ(char **argv, unsigned char *memory,
		int *player_number, int nb_champ)
{
	t_header		*champs;
	int				i;
	int				j;
	int				fd;

	if (!(champs = (t_header*)malloc(sizeof(t_header) * nb_champ)))
		return (0);
	i = -1;
	j = 0;
	while (++i < nb_champ)
	{
		while (player_number[j] == 0)
			j++;
		if ((fd = open(*(argv + player_number[j] - 1), O_RDONLY)) < 1)
			return (ft_free_error(champs));
		if (ft_extract_header(fd, champs + i) < 1)
			return (ft_free_error(champs));
		if (ft_extract_prog(fd, champs + i,
					(memory + i * (MEM_SIZE / nb_champ))) < 1)
			return (ft_free_error(champs));
		j++;
		if (close(fd) == -1)
			return (ft_free_error(champs));
	}
	return (champs);
}

int					ft_load(char **argv, t_settings *sets)
{
	int				nb_champ;
	int				player_number[MAX_ARGS_NUMBER];

	sets->options = 0;
	if (!(nb_champ = ft_manage_entry(argv, player_number, sets)))
		return (0);
	if (!(sets->champs = ft_insert_champ(argv, sets->memory, player_number,
		nb_champ)))
		return (0);
	return (nb_champ);
}
