/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_u_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:41:50 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/05 14:46:03 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf_bonus.h"

static int	ft_num_len(unsigned int n, t_flags *flags)
{
	int	len;

	if (n == 0 && flags->precision == 0)
		len = 0;
	else
		len = 1;
	while (n / 10 != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	ft_print_number(t_flags *flags, int len, unsigned int n)
{
	int	i;

	i = 0;
	while (i++ < (flags->precision - len))
		flags->printed += write(1, "0", 1);
	if (!(n == 0 && flags->precision == 0))
		ft_putnbr_unsigned(n, flags);
}

void	ft_print_u(va_list args, t_flags *flags)
{
	unsigned int	n;
	int				num_len;
	int				true_len;

	n = va_arg(args, unsigned int);
	num_len = ft_num_len(n, flags);
	if (flags->precision > num_len)
		true_len = flags->precision;
	else
		true_len = num_len;
	if (flags->width > true_len)
	{
		if (flags->dash == 1)
		{
			ft_print_number(flags, num_len, n);
			ft_print_filling(flags, true_len);
		}
		else
		{
			ft_print_filling(flags, true_len);
			ft_print_number(flags, num_len, n);
		}
	}
	else
		ft_print_number(flags, num_len, n);
}
