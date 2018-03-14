/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenis <adenis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 17:28:11 by adenis            #+#    #+#             */
/*   Updated: 2017/10/30 13:32:05 by adenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	print_magic(unsigned int nb)
{
	ft_putchar_fd((char)(nb >> 24), FD);
	ft_putchar_fd((char)(nb >> 16), FD);
	ft_putchar_fd((char)(nb >> 8), FD);
	ft_putchar_fd((char)nb, FD);
}
