/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 11:27:11 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/04/16 12:33:46 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	n_option(char **args, int *i)
{
	int	n;
	int	j;
	int	k;

	n = 0;
	j = 0;
	while (!ft_strncmp(args[j], "-n", 2))
	{
		k = 1;
		while (args[j][k] == 'n')
			k++;
		if (args[j][k] == '\0')
		{
			*i = j + 1;
			n = 1;
		}
		else
		{
			*i = j;
			break ;
		}
		j++;
	}
	return (n);
}

void	ft_echo(t_data *data, t_cmd *com)
{
	int	n;
	int	i;

	i = 0;
	if (!com->args)
	{
		write(1, "\n", 1);
		data->ret = 0;
		return ;
	}
	n = n_option(com->args, &i);
	while (i < com->n_args)
	{
		write(1, com->args[i], ft_strlen(com->args[i]));
		if (i < com->n_args - 1)
			write(1, " ", 1);
		i++;
	}
	if (n == 0)
		write(1, "\n", 1);
	data->ret = 0;
}
