/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:01:49 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/05/05 12:12:10 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals_dad(int sig)
{
	if (sig == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
	else if (sig == SIGINT)
	{
		write(1, "\b\b  \b\b\n", 7);
		prompt();
	}
}

void	signals_son(int sig)
{
	if (sig == SIGQUIT)
		write(1, "Quit: 3\n", 8);
	else if (sig == SIGINT)
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
