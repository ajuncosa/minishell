/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_d_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:40:42 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/03/10 12:42:58 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf_bonus.h"

static int	ft_num_len(int n, t_flags *flags)
{
	int	i;
	int	num_len;

	num_len = (n == 0 && flags->precision == 0) ? 0 : 1;
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
	int true_len;

	true_len = num_len;
	if (flags->precision > num_len)
		true_len = flags->precision;
	if (n < 0)
		true_len++;
	else if (n >= 0 && (flags->plus == 1 || flags->space == 1))
		true_len++;
	return (true_len);
}

static void	ft_print_number(int n, t_flags *flags, int num_len)
{
	int i;

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

static void	ft_print_width_nodash(t_flags *flags, int num_len, int true_len,
		unsigned int n)
{
	if (n < 0 && flags->zero == 1)
	{
		n = -n;
		flags->printed += write(1, "-", 1);
	}
	if (flags->plus == 1 && n >= 0 && flags->zero == -1)
	{
		ft_print_filling(flags, true_len);
		flags->printed += write(1, "+", 1);
	}
	else if (flags->plus == 1 && n >= 0 && flags->zero == 1)
	{
		flags->printed += write(1, "+", 1);
		ft_print_filling(flags, true_len);
	}
	else
		ft_print_filling(flags, true_len);
	ft_print_number(n, flags, num_len);
}

void		ft_print_d(va_list args, t_flags *flags)
{
	int	n;
	int	num_len;
	int	true_len;

	n = va_arg(args, int);
	num_len = ft_num_len(n, flags);
	true_len = ft_true_len(n, flags, num_len);
	if (flags->space == 1 && n >= 0)
		flags->printed += write(1, " ", 1);
	if (flags->width > true_len)
		if (flags->dash == 1)
		{
			if (flags->plus == 1 && n >= 0)
				flags->printed += write(1, "+", 1);
			ft_print_number(n, flags, num_len);
			ft_print_filling(flags, true_len);
		}
		else
			ft_print_width_nodash(flags, num_len, true_len, n);
	else
	{
		if (flags->plus == 1 && n >= 0)
			flags->printed += write(1, "+", 1);
		ft_print_number(n, flags, num_len);
	}
}
