/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:13:14 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/02/28 16:43:10 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_num_len(unsigned int n, t_flags *flags)
{
	int	len;

	len = (n == 0 && flags->precision == 0) ? 0 : 1;
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
	(n == 0 && flags->precision == 0) ? 0 : ft_putnbr_unsigned(n, flags);
}

void		ft_print_u(va_list args, t_flags *flags)
{
	unsigned int	n;
	int				num_len;
	int				true_len;

	n = va_arg(args, unsigned int);
	num_len = ft_num_len(n, flags);
	true_len = (flags->precision > num_len) ? flags->precision : num_len;
	if (flags->width > true_len)
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
	else
		ft_print_number(flags, num_len, n);
}
