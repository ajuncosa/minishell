/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_x_lower_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:42:28 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/03/09 14:22:20 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf_bonus.h"

static int	ft_num_len(t_flags *flags, unsigned int n)
{
	int	len;

	len = (flags->precision == 0 && n == 0) ? 0 : 1;
	while (n / 16 != 0)
	{
		len++;
		n /= 16;
	}
	return (len);
}

static void	ft_print_num(t_flags *flags, unsigned int n, int len)
{
	int	i;

	i = 0;
	while (i < (flags->precision - len))
	{
		i++;
		flags->printed += write(1, "0", 1);
	}
	(flags->precision == 0 && n == 0) ? 0 : ft_print_hexa(n, 'l', flags);
}

static void	ft_print_width(t_flags *flags, int num_len, int true_len,
		unsigned int n)
{
	if (flags->dash == 1)
	{
		if (flags->hash == 1)
			flags->printed += write(1, "0x", 2);
		ft_print_num(flags, n, num_len);
		ft_print_filling(flags, true_len);
	}
	else
	{
		if (flags->hash == 1 && flags->zero == -1)
		{
			ft_print_filling(flags, true_len);
			flags->printed += write(1, "0x", 2);
		}
		else if (flags->hash == 1 && flags->zero == 1)
		{
			flags->printed += write(1, "0x", 2);
			ft_print_filling(flags, true_len);
		}
		else
			ft_print_filling(flags, true_len);
		ft_print_num(flags, n, num_len);
	}
}

void		ft_print_x_lower(va_list args, t_flags *flags)
{
	unsigned int	n;
	int				num_len;
	int				true_len;

	n = va_arg(args, unsigned int);
	num_len = ft_num_len(flags, n);
	true_len = (flags->precision > num_len) ? flags->precision : num_len;
	if (n == 0)
		flags->hash = -1;
	if (flags->hash == 1)
		true_len += 2;
	if (flags->width > true_len)
		ft_print_width(flags, num_len, true_len, n);
	else
	{
		if (flags->hash == 1)
			flags->printed += write(1, "0x", 2);
		ft_print_num(flags, n, num_len);
	}
}
