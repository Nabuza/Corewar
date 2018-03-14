/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaloul <nagaloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 19:22:01 by nagaloul          #+#    #+#             */
/*   Updated: 2017/11/21 13:32:00 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"
#include "op.h"

t_list		*ft_create_elem(char *data)
{
	t_list	*elem;

	elem = NULL;
	if (!(elem = malloc(sizeof(t_list))))
		exit(0);
	elem->content = ft_strdup(data);
	elem->next = NULL;
	return (elem);
}
