/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:11:07 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/03/04 15:29:03 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

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

void		ft_print_x_lower(va_list args, t_flags *flags)
{
	unsigned int	n;
	int				num_len;
	int				true_len;

	n = va_arg(args, unsigned int);
	num_len = ft_num_len(flags, n);
	true_len = (flags->precision > num_len) ? flags->precision : num_len;
	if (flags->width > true_len)
		if (flags->dash == 1)
		{
			ft_print_num(flags, n, num_len);
			ft_print_filling(flags, true_len);
		}
		else
		{
			ft_print_filling(flags, true_len);
			ft_print_num(flags, n, num_len);
		}
	else
		ft_print_num(flags, n, num_len);
}
