/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 10:32:36 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/02/28 12:26:03 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_print_hexa(size_t nbr, char whatcase, t_flags *flags)
{
	char	b;

	if (nbr >= 16)
		ft_print_hexa(nbr / 16, whatcase, flags);
	b = nbr % 16;
	if (b > 9)
	{
		if (whatcase == 'l')
			b = b + 87;
		if (whatcase == 'u')
			b = b + 55;
	}
	else
		b = b + '0';
	flags->printed += write(1, &b, 1);
}

void	ft_putnbr_unsigned(unsigned int n, t_flags *flags)
{
	char number;

	if (n > 9)
		ft_putnbr_unsigned(n / 10, flags);
	number = (n % 10) + '0';
	flags->printed += write(1, &number, 1);
}

void	ft_print_filling(t_flags *flags, int len)
{
	int i;

	i = 0;
	if (flags->zero == 1)
		while (i++ < (flags->width - len))
			flags->printed += write(1, "0", 1);
	else
		while (i++ < (flags->width - len))
			flags->printed += write(1, " ", 1);
}

void	ft_putnbr_fd_edit(int n, int fd, t_flags *flags)
{
	char	c;
	long	nb;

	if (n == 0 && flags->precision == 0)
		return ;
	nb = n;
	if (nb < 0)
	{
		nb = nb * -1;
		flags->printed += write(fd, "-", 1);
	}
	if (nb / 10 > 0)
		ft_putnbr_fd_edit(nb / 10, fd, flags);
	c = (nb % 10) + '0';
	flags->printed += write(fd, &c, 1);
}

void	ft_putstr_fd_edit(char *s, int fd, t_flags *flags)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		flags->printed += write(fd, &s[i], 1);
		i++;
	}
}
