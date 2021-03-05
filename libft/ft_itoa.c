/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 11:31:01 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/05 13:46:56 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n)
{
	int	len;

	len = 1;
	while (n / 10 != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static void	ft_fill_string(char *str, long n, int i)
{
	char	c;

	if (n / 10 > 0)
		ft_fill_string(str, n / 10, i - 1);
	c = n % 10 + '0';
	str[i] = c;
}

char	*ft_itoa(int n)
{
	int		len;
	long	nb;
	char	*str;

	len = ft_count(n);
	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	ft_fill_string(str, nb, len - 1);
	str[len] = '\0';
	return (str);
}
