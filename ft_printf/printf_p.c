/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:08:14 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/03/09 13:16:17 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_address_len(t_flags *flags, size_t address)
{
	int	len;

	len = (flags->precision == 0 && address == 0) ? 0 : 1;
	while (address / 16 != 0)
	{
		len++;
		address /= 16;
	}
	return (len);
}

static void	ft_print_address(t_flags *flags, size_t address, int len)
{
	flags->printed += write(1, "0x", 2);
	if (flags->precision == 0 && address == 0)
		return ;
	while (flags->precision > len)
	{
		flags->printed += write(1, "0", 1);
		len++;
	}
	ft_print_hexa(address, 'l', flags);
}

void		ft_print_p(va_list args, t_flags *flags)
{
	void	*ptr;
	size_t	address;
	int		addr_len;
	int		true_len;

	ptr = va_arg(args, void *);
	address = (size_t)ptr;
	addr_len = ft_address_len(flags, address);
	true_len = (flags->precision > addr_len) ? flags->precision : addr_len;
	if (flags->width > true_len)
		if (flags->dash == 1)
		{
			ft_print_address(flags, address, addr_len);
			ft_print_filling(flags, true_len + 2);
		}
		else
		{
			ft_print_filling(flags, true_len + 2);
			ft_print_address(flags, address, addr_len);
		}
	else
		ft_print_address(flags, address, addr_len);
}
