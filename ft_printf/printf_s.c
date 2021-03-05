/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:06:18 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/05 14:43:12 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_print_s(va_list args, t_flags *flags)
{
	char	*str;
	int		len;

	str = ft_strdup(va_arg(args, char *));
	if (str == NULL)
		str = ft_strdup("(null)");
	if (flags->precision != -1)
		str = ft_substr(str, 0, flags->precision);
	len = ft_strlen(str);
	if (flags->width != -1)
	{
		if (flags->dash == 1)
		{
			ft_putstr_fd_edit(str, 1, flags);
			if (len < flags->width)
				ft_print_filling(flags, len);
		}
		else
		{
			if (len < flags->width)
				ft_print_filling(flags, len);
			ft_putstr_fd_edit(str, 1, flags);
		}
	}
	else
		ft_putstr_fd_edit(str, 1, flags);
	free(str);
}
