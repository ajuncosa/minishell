/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_n_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:38:24 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/03/09 11:55:59 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf_bonus.h"

void	ft_manage_n(va_list args, t_flags *flags)
{
	int	*n_chars;

	n_chars = va_arg(args, int *);
	*n_chars = flags->printed;
}
