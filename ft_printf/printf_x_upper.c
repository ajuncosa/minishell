/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_x_upper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:12:49 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/05 14:54:40 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_num_len(t_flags *flags, unsigned int n)
{
	int	len;

	if (flags->precision == 0 && n == 0)
		len = 0;
	else
		len = 1;
	while (n / 16 > 0)
	{
		n /= 16;
		len++;
	}
	return (len);
}

static void	ft_print_number(t_flags *flags, unsigned int n, int len)
{
	int	i;

	i = 0;
	while (i < (flags->precision - len))
	{
		i++;
		flags->printed += write(1, "0", 1);
	}
	if (!(flags->precision == 0 && n == 0))
		ft_print_hexa(n, 'u', flags);
}

void	ft_print_x_upper(va_list args, t_flags *flags)
{
	unsigned int	n;
	int				num_len;
	int				true_len;

	n = va_arg(args, unsigned int);
	num_len = ft_num_len(flags, n);
	if (flags->precision > num_len)
		true_len = flags->precision;
	else
		true_len = num_len;
	if (flags->width > true_len)
	{
		if (flags->dash == 1)
		{
			ft_print_number(flags, n, num_len);
			ft_print_filling(flags, true_len);
		}
		else
		{
			ft_print_filling(flags, true_len);
			ft_print_number(flags, n, num_len);
		}
	}
	else
		ft_print_number(flags, n, num_len);
}
