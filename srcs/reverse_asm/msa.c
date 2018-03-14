/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 17:56:31 by adenis            #+#    #+#             */
/*   Updated: 2017/11/14 18:47:35 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msa.h"

int			isop(char *s)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!s || ft_strlen(s) <= 1)
		return (0);
	(tmp = ft_strsub(s, 0, ft_strlen(s) - 1)) ? 0 : ft_error("error");
	while (i < 16)
	{
		if (!ft_strcmp(tmp, g_op_tab[i].label))
		{
			tmp ? ft_strdel(&tmp) : 0;
			return (1);
		}
		i++;
	}
	tmp ? ft_strdel(&tmp) : 0;
	return (0);
}

int			handle_file(char *s)
{
	char	*s2;
	char	*name;

	if (!s)
		exit(0);
	if (!ft_strrchr(s, '.'))
		return (ft_error(NULL));
	if (!ft_strstr(ft_strrchr(s, '.'), "cor"))
		return (ft_error(NULL));
	if (!(s2 = ft_strdup(s)))
		exit(0);
	s2[ft_strrchr(s2, '.') - s2] = 0;
	if (!(name = ft_strjoin(s2, "_r.s")))
		exit(0);
	FD = open(name, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	FD ? 0 : ft_error("can't create output file\n");
	ft_printf("Writing output program to %s\n", name);
	free(s2);
	free(name);
	return (0);
}

void		handle_tabs(void)
{
	t_list		*tmp;
	char		*s;
	char		*s2;

	tmp = OUT;
	s2 = NULL;
	s = NULL;
	while (tmp)
	{
		if (isop(tmp->content))
		{
			s = tmp->content;
			s[ft_strlen(s) - 1] = '\t';
			if (ft_strlen(s) < 5)
			{
				s2 = s;
				(s = ft_strjoin(s, "\t")) ? 0 : ft_error("error");
				s2 ? free(s2) : 0;
			}
			(tmp->content = ft_strjoin("\t", s)) ? 0 : ft_error("error");
			s ? free(s) : 0;
		}
		tmp = tmp->next;
	}
}

void		ft_msa(int fd, char *file)
{
	t_oct	*lst;

	lst = get_input(fd);
	LST = lst;
	LINE = NULL;
	OUT = NULL;
	LAB = 1;
	lst = input_checks();
	get_header(&lst);
	lst_val(lst);
	get_values(lst);
	out_val();
	handle_label();
	handle_last();
	handle_file(file);
	handle_tabs();
	display_out();
	clean();
}

int			main(int argc, char **argv)
{
	int		fd;

	FD = 1;
	if (argc != 2)
		return (ft_usage());
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (ft_error("can't open the file"));
	ft_msa(fd, argv[1]);
	if (close(fd) == -1)
		return (ft_error("close fd failed"));
}
