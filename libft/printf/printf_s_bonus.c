/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_s_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:41:29 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/03/09 11:41:36 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf_bonus.h"

void		ft_print_s(va_list args, t_flags *flags)
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
		if (flags->dash == 1)
		{
			ft_putstr_fd_edit(str, 1, flags);
			(len < flags->width) ? ft_print_filling(flags, len) : 0;
		}
		else
		{
			(len < flags->width) ? ft_print_filling(flags, len) : 0;
			ft_putstr_fd_edit(str, 1, flags);
		}
	else
		ft_putstr_fd_edit(str, 1, flags);
	free(str);
}
