/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:01:49 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/04/28 18:21:05 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit(int sig)
{
	if (g_pid == -1)
	{
		write(1, "\b\b", 2);
		write(1, "  ", 2);
		write(1, "\b\b", 2);
	}
	else if (g_pid > 0)
		write(1, "Quit: 3\n", 8);
}

void	ctrl_c(int sig)
{
	if (g_pid == -1)
	{
		write(1, "\b\b", 2);
		write(1, "  ", 2);
		write(1, "\b\b", 2);
		write(1, "\n\033[1;37m", 9);
		write(1, g_user, ft_strlen(g_user));
		write(1, "> ", 2);
		write(1, "\033[0m", 4);
	}
	else if (g_pid > 0)
		write(1, "\n", 1);
}

void	ctrl_d(int ctrl, char **str, t_data *data)
{
	char	*buf;
	char	*tmp;

	buf = NULL;
	tmp = NULL;
	if ((*str)[0] != '\0')
		buf = *str;
	while (ctrl == 0 && buf)
	{
		ctrl = get_next_line(0, str);
		tmp = ft_strjoin(buf, *str);
		free(buf);
		buf = tmp;
		free(*str);
	}
	if (buf)
		*str = buf;
	if (!ctrl && !buf)
	{
		free(*str);
		ft_exit(data, NULL);
	}
}
