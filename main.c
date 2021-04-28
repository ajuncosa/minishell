/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:36:03 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/04/28 18:08:52 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_init(t_data *data)
{
	data->cmd_head = NULL;
	data->ret = 0;
	g_user = NULL;
	g_pid = -1;
}

int	main(int argc, char **argv, char **envp)
{
	int		ctrl;
	char	*str;
	t_data	data;

	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, quit);
	start_init(&data);
	header();
	lst_env(&data, envp);
	set_user(&data);
	del_oldpwd(&data);
	while (1)
	{
		data.line = NULL;
		prompt();
		ctrl = get_next_line(0, &str);
		if (!ctrl)
			ctrl_d(ctrl, &str, &data);
		parser(&data, str, envp);
		free(str);
	}
	ft_exit(&data, NULL);
	return (0);
}
