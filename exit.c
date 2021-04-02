/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 12:47:45 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/04/02 16:25:22 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_lst(void *env)
{
	free(((t_env*)env)->id);
	free(((t_env*)env)->value);
	free((t_env*)env);
}

void	del_lst_cmd(void *cmd)
{
	int j;

	if (((t_cmd*)cmd)->cmd)
		free(((t_cmd*)cmd)->cmd);
	j = 0;
	while (j < ((t_cmd*)cmd)->n_args)
	{
		free(((t_cmd*)cmd)->args[j]);
		j++;
	}
	if (((t_cmd*)cmd)->args)
		free(((t_cmd*)cmd)->args);
	free((t_cmd*)cmd);
}

void	ft_exit(t_data data)
{
	/*int	i;
	int	r;

	if (!ft_strcmp(com->cmd, "exit"))
	{
		if (com->n_args > 1)
		{
			printf("exit: too many arguments\n");
			ret = 1;
			return ;
		}
		if (com->n_args > 0)
		{
			i = 0;
			r = ft_atoi(com->args[0]);
			while(com->args[0][i])
			{
				if (!ft_isdigit(com->args[0][i]))
				{
					printf("exit: %s: numeric argument required\n", com->args[0]);
					r = 255;
					break ;
				}
				i++;
			}
		}
	}
	*/
	if (user)
		free(user);
	ft_lstclear(&data.cmd_head, &del_lst_cmd);
	ft_lstclear(&data.env_head, &del_lst);
	exit(0);
}