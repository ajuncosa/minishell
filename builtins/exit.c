/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 12:47:45 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/05/05 11:44:54 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_lst(void *env)
{
	free(((t_env *)env)->id);
	free(((t_env *)env)->value);
	free((t_env *)env);
}

void	del_lst_cmd(void *cmd)
{
	int	j;

	if (((t_cmd *)cmd)->cmd)
		free(((t_cmd *)cmd)->cmd);
	if (((t_cmd *)cmd)->args_str)
	{
		j = 0;
		while (j < ((t_cmd *)cmd)->n_args)
		{
			free(((t_cmd *)cmd)->args_str[j]);
			j++;
		}
		free(((t_cmd *)cmd)->args_str);
	}
	if (((t_cmd *)cmd)->args)
	{
		j = 0;
		while (j < ((t_cmd *)cmd)->n_args)
		{
			free(((t_cmd *)cmd)->args[j]);
			j++;
		}
		free(((t_cmd *)cmd)->args);
	}
	free((t_cmd *)cmd);
}

void	check_exit_args(t_data *data, t_cmd *com)
{
	int	i;

	i = 0;
	data->ret = ft_atoi(com->args_str[0]);
	if (data->ret >= 256)
		data->ret -= 256;
	else if (data->ret < 0)
		data->ret += 256;
	if (com->args_str[0][0] == '-')
	{
		if (com->args_str[0][1] == '-' && com->args_str[0][2] == '\0')
			i = 2;
		else if (ft_isdigit(com->args_str[0][1]))
			i = 1;
	}
	while (com->args_str[0][i])
	{
		if (!ft_isdigit(com->args_str[0][i]))
		{
			printf("exit: %s: numeric argument required\n", com->args_str[0]);
			data->ret = 255;
			break ;
		}
		i++;
	}
}

void	ft_exit(t_data *data, t_cmd *com)
{
	int	i;

	printf("exit\n");
	if (com)
	{
		if (!ft_strcmp(com->cmd, "exit"))
		{	
			if (com->n_args > 1)
			{
				printf("exit: too many arguments\n");
				data->ret = 1;
				return ;
			}
			if (com->n_args > 0)
				check_exit_args(data, com);
		}
	}
	if (data->user)
		free(data->user);
	if (data->line)
		free(data->line);
	ft_lstclear(&data->cmd_head, &del_lst_cmd);
	ft_lstclear(&data->env_head, &del_lst);
	exit(data->ret);
}
