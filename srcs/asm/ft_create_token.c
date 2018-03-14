/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaloul <nagaloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 19:22:01 by nagaloul          #+#    #+#             */
/*   Updated: 2017/11/21 13:31:56 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"
#include "op.h"

t_token		*ft_create_token(char *data, int i, int b)
{
	t_token	*elem;

	elem = NULL;
	if (!(elem = (t_token *)malloc(sizeof(t_token))))
		exit(0);
	elem->unknow = ft_strdup(data);
	elem->col = i;
	elem->lan = b;
	elem->lab = NULL;
	elem->comment = NULL;
	elem->dirlab = NULL;
	elem->indirlab = NULL;
	elem->dir = NULL;
	elem->name = NULL;
	elem->ncom = NULL;
	elem->indir = NULL;
	elem->inst = NULL;
	elem->reg = NULL;
	elem->next = NULL;
	return (elem);
}
