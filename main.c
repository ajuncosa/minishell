/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:36:03 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/05/05 12:16:17 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_init(t_data *data)
{
	data->cmd_head = NULL;
	data->ret = 0;
	data->user = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	int		ctrl;
	char	*str;
	t_data	data;

	data.envp = envp;
	start_init(&data);
	header();
	lst_env(&data);
	set_user(&data);
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
