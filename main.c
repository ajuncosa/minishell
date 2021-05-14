/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:36:03 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/05/14 13:58:55 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		ctrl;
	char	*str;
	t_data	data;

	data.envp = envp;
	data.cmd_head = NULL;
	data.ret = 0;
	header();
	lst_env(&data);
	del_oldpwd(&data);
	while (1)
	{
		signal(SIGINT, signals_dad);
		signal(SIGQUIT, signals_dad);
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
