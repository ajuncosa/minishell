/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:30:37 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/05/04 13:30:54 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msn(char *cmd, char *str, char *txt)
{
	if (cmd && str && txt)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
		write(2, str, ft_strlen(str));
		write(2, ": ", 2);
		write(2, txt, ft_strlen(txt));
		write(2, "\n", 1);
	}
	else if (cmd && txt)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
		write(2, txt, ft_strlen(txt));
		write(2, "\n", 1);
	}
}

void	fork_errors(void)
{
	char	*sterr;

	sterr = strerror(errno);
	error_msn(NULL, NULL, sterr);
}
