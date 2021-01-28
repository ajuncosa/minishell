/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_c_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:40:20 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/03/09 11:40:27 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf_bonus.h"

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
