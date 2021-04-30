/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:36:03 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/04/30 18:49:54 by ajuncosa         ###   ########.fr       */
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

	data.envp = envp;
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, quit);
	start_init(&data);
	header();
	lst_env(&data);
	set_user(&data);
	del_oldpwd(&data);
	while (1)
	{
		data.line = NULL;
		prompt();
		ctrl = get_next_line(0, &str);
		if (!ctrl)
			ctrl_d(ctrl, &str, &data);
		parser(&data, str);
		free(str);
	}
	ft_exit(&data, NULL);
	return (0);
}
