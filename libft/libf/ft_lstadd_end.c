/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 15:14:19 by adenis            #+#    #+#             */
/*   Updated: 2017/11/10 17:14:00 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

void			ft_lstadd_end(t_list *alst, t_list *new)
{
	if (!alst)
		return ;
	while (alst->next)
		alst = alst->next;
	alst->next = new;
}
