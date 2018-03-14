/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolivier <nolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 12:17:53 by nolivier          #+#    #+#             */
/*   Updated: 2017/11/22 14:22:22 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H
# define ASSEMBLER_H
# include "op.h"
# include "../libft/inc/libftprintf.h"
# define OUT g_out
# define OPS g_ops
# define FD g_fd
# define TOK g_tok
# define PROG_SIZE g_prog_size

typedef	struct		s_token
{
	struct s_token	*next;
	int				lan;
	int				col;
	char			*lab;
	char			*comment;
	char			*dirlab;
	char			*indirlab;
	char			*dir;
	char			*name;
	char			*ncom;
	char			*indir;
	char			*inst;
	char			*reg;
	char			*unknow;
}					t_token;

typedef	struct		s_output
{
	struct s_output	*next;
	struct s_output	*link;
	int				type;
	char			*name;
	int				val;
	int				size;
	int				pos;
}					t_output;

void				init_ft_tab(void);
void				leave(void);

void				get_ops(t_list **ops, int fd);
t_output			*new_output(char *name, int type);
void				fill_output(void);
void				create_output(t_token *token);
void				link_op(t_output *op, int narg);
void				link_output(void);

void				print_val(void);
void				print_header(void);
void				print_magic(unsigned int nb);

void				del(void *content, size_t size);
void				display_lst(t_list *lst);
int					ft_error(void);
int					ft_usage(void);
t_list				*get_input(int fd);
int					isop(char *s);
char				*getattribute(t_token *tok);
unsigned int		magic_n_size(unsigned int n);

t_output			*get_dirlab(char *s);
int					calc_dirlab(short a, short b);
void				fill_dirlab(void);

t_token				*new_token(char *s);
void				token_add(t_token *split, t_token *new);
void				tokenize_lst(t_list *lst, t_token *split);
void				token_assign(t_token *token);
void				specify_tokens(t_token *token);

int					handle_file(char *s);

int					whichop(char *s);
int					isop(char *s);
int					get_value(t_token *token);

void				ft_calc(t_token *tok);
int					ft_opc(t_output *pop);

void				out_lab(t_output *pop);
void				out_comment(t_output *pop);
void				out_dirlab(t_output *pop);
void				out_indirlab(t_output *pop);
void				out_dir(t_output *pop);
void				out_name(t_output *pop);
void				out_ncom(t_output *pop);
void				out_indir(t_output *pop);
void				out_inst(t_output *pop);
void				out_reg(t_output *pop);

void				free_tok(t_token *tok);
void				del(void *content, size_t size);
void				free_out(t_output *lst);
void				clean();
int					ft_lastline(char *str);
void				ft_naco(t_token **tok, char *str, int *count, int *b);
void				ft_naco2(t_token **tok, char *str, int *b);
int					ft_sti(t_token *tok, int i, t_token *lab, t_list *sep);
int					ft_ldi(t_token *tok, int i, t_token *lab, t_list *sep);
int					ft_or(t_token *tok, int i, t_token *lab, t_list *sep);
int					ft_aff(t_token *tok, int i, t_token *lab, t_list *sep);
void				read_check(int	fd, t_list *ops);

int					ft_checkop(t_op g_op_tab, t_token *tok, t_token *temp, \
					t_list *sep);
int					ft_real(t_token *tok, t_token *temp, t_list *sep);
int					ft_instruc(t_token **tok, t_token *temp, t_list *sep);
int					ft_label(t_token **tok);
int					ft_check_every(t_token *tok, t_list *sep);
int					ft_check_commands(t_token **tok);
int					ft_check_commands2(t_token **tok);
int					ft_check(t_token *tok, t_list *sep);

t_list				*ft_create_elem(char *data);
t_token				*ft_create_token(char *data, int i, int b);
void				ft_freetab(char **tab);

int					ft_sub(t_token *tok, int i, t_token *lab, t_list *sep);
int					ft_st(t_token *tok, int i, t_token *lab, t_list *sep);
int					ft_ld(t_token *tok, int i, t_token *lab, t_list *sep);
int					ft_live(t_token *tok, int i, t_token *temp, t_list *sep);

int					onlysep(t_token **tok);
void				ft_comment(t_token *tok);
void				ft_lab(t_token *tok);
void				ft_pindirlab(t_token *tok);
void				ft_pdirlab(t_token *tok);
void				ft_pindir(t_token *tok);
void				ft_name(t_token *tok);
void				ft_ncom(t_token *tok);
void				ft_pdir(t_token *tok);
void				ft_inst(t_token *tok);
void				ft_preg(t_token *tok);
void				ft_pars(t_token *tok);

void				ft_push_back(t_list **begin_list, char *data);
void				ft_push_token(t_token **begin_list, char *data, int i, \
					int b);

void				ft_puterror(t_token *tok, int i, int a, t_token *temp);

void				ft_puterrorsep(int i);

int					ft_indir(t_token *tok, int i, t_token *temp);
int					ft_indirlab(char *tok, t_token *temp);
int					ft_dirlab(char *tok, t_token *temp);
int					ft_dir(t_token *tok, int i, t_token *temp);
int					ft_reg(t_token *tok, int i);

int					ft_tomuch(t_token *tok, int i);

int					ft_finishim(char **tab);
int					ft_finish(char **tab, char *inst);
int					ft_virgule(int i, t_list *sep, int c, char *inst);

int					count_l(char *str);
void				filltab(char *tab, char *str);
void				counttab(char **tab, char *str);
int					count_w(char *str);
char				**split_space(char *str);

int					ft_sep(char *str);
void				ft_guill(t_token **tok, char *str, int *count, int b);
void				ft_try(t_token **tok, char *str, int *count, int b);
void				split_tok(t_token **tok, char *str, int b);
void				split_head(t_token **tok, t_list **head, int *i);
void				ft_medium(t_token **tok, char *str, int *a);
void				ft_hard(t_token **tok, t_list **line, int *b);

int					ft_countchar(char *str, char c);
int					ft_decoupe(char const *s);
char				ft_lastchar(char *str);
char				**ft_remp(char **tab, char const *s, int g);
char				**my_split(char const *s);

void				display_lst(t_list *lst);
int					ft_error(void);
int					ft_usage(void);

typedef void		(*t_ftype) (t_output *);

t_list				*g_ops;
t_ftype				g_ft_tab[10];
t_output			*g_out;
t_token				*g_tok;
int					g_fd;
int					g_prog_size;
int					g_name;
#endif
