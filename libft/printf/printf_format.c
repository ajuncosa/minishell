/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 10:48:52 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/03/04 15:15:49 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		ft_choose_format(va_list args, char a, t_flags *flags)
{
	if (a == 'c')
		ft_print_c(va_arg(args, int), flags);
	else if (a == 's')
		ft_print_s(args, flags);
	else if (a == 'd' || a == 'i')
		ft_print_d(args, flags);
	else if (a == 'p')
		ft_print_p(args, flags);
	else if (a == 'u')
		ft_print_u(args, flags);
	else if (a == 'x')
		ft_print_x_lower(args, flags);
	else if (a == 'X')
		ft_print_x_upper(args, flags);
	else if (a == '%')
		ft_print_c('%', flags);
	else
		write(1, &a, 1);
}

void		ft_reset_flags(t_flags *flags)
{
	flags->dash = -1;
	flags->zero = -1;
	flags->width = -1;
	flags->precision = -1;
}

static void	ft_identify_dash_and_zero(const char *s, int *i, t_flags *flags)
{
	while (s[*i] == '-' || s[*i] == '0')
	{
		if (s[*i] == '-')
		{
			flags->dash = 1;
			flags->zero = -1;
		}
		if (s[*i] == '0' && flags->dash == -1)
			flags->zero = 1;
		*i = *i + 1;
	}
}

void		ft_identify_flags(va_list args, const char *s, int i,
		t_flags *flags)
{
	ft_identify_dash_and_zero(s, &i, flags);
	if (s[i] == '*')
	{
		flags->width = va_arg(args, int);
		if (flags->width < 0)
		{
			flags->width = -flags->width;
			flags->dash = 1;
			flags->zero = -1;
		}
		i++;
	}
	if (s[i] > '0' && s[i] <= '9')
	{
		flags->width = ft_atoi(&s[i]);
		while (s[i] >= '0' && s[i] <= '9')
			i++;
	}
	if (s[i++] == '.')
	{
		flags->precision = 0;
		flags->zero = -1;
		flags->precision = (s[i] == '*') ? va_arg(args, int) : ft_atoi(&s[i]);
		flags->precision = (flags->precision < 0) ? -1 : flags->precision;
	}
}
