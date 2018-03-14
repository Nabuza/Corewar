/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 15:22:11 by adenis            #+#    #+#             */
/*   Updated: 2017/11/23 11:42:36 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void				free_tok(t_token *tok)
{
	if (tok->next)
		free_tok(tok->next);
	tok->unknow ? free(tok->unknow) : NULL;
	tok ? free(tok) : NULL;
}

void				del(void *content, size_t size)
{
	size = 0;
	free(content);
}

void				free_out(t_output *lst)
{
	if (lst->next)
		free_out(lst->next);
	if (lst->type == 7 || lst->type == 2)
		lst->name ? free(lst->name) : NULL;
	free(lst);
}

void				leave(void)
{
	ft_printf("error\n");
	clean();
}

void				clean(void)
{
	if (OPS)
		ft_lstdel(&OPS, &del);
	if (TOK)
		free_tok(TOK);
	if (OUT)
		free_out(OUT);
	exit(0);
}
