/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:05:15 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/02/27 17:21:28 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_print_c(int a, t_flags *flags)
{
	if (flags->width != -1)
	{
		if (flags->dash == 1)
		{
			flags->printed += write(1, &a, 1);
			ft_print_filling(flags, 1);
		}
		else
		{
			ft_print_filling(flags, 1);
			flags->printed += write(1, &a, 1);
		}
	}
	else
		flags->printed += write(1, &a, 1);
}
