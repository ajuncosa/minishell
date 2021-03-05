/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:07:26 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/05 14:33:52 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_num_len(int n, t_flags *flags)
{
	int	i;
	int	num_len;

	if (n == 0 && flags->precision == 0)
		num_len = 0;
	else
		num_len = 1;
	i = n;
	while (i / 10 != 0)
	{
		i = i / 10;
		num_len++;
	}
	return (num_len);
}

static int	ft_true_len(int n, t_flags *flags, int num_len)
{
	int	true_len;

	true_len = num_len;
	if (flags->precision > num_len)
		true_len = flags->precision;
	if (n < 0)
		true_len++;
	return (true_len);
}

static void	ft_print_number(int n, t_flags *flags, int num_len)
{
	int	i;

	if (n < 0 && flags->precision > num_len)
	{
		n = -n;
		flags->printed += write(1, "-", 1);
	}
	i = 0;
	while (i++ < (flags->precision - num_len))
		flags->printed += write(1, "0", 1);
	ft_putnbr_fd_edit(n, 1, flags);
}

void	ft_print_d(va_list args, t_flags *flags)
{
	int	n;
	int	num_len;
	int	true_len;

	n = va_arg(args, int);
	num_len = ft_num_len(n, flags);
	true_len = ft_true_len(n, flags, num_len);
	if (flags->width != -1)
	{
		if (flags->dash == 1)
		{
			ft_print_number(n, flags, num_len);
			if (true_len < flags->width)
				ft_print_filling(flags, true_len);
		}
		else
		{
			if (n < 0 && flags->zero == 1)
			{
				n = -n;
				flags->printed += write(1, "-", 1);
			}
			if (true_len < flags->width)
				ft_print_filling(flags, true_len);
			ft_print_number(n, flags, num_len);
		}
	}
	else
		ft_print_number(n, flags, num_len);
}
