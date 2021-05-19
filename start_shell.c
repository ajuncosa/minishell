/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:00:46 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/05/19 14:12:04 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	header(void)
{
	write(1, "\e[1;1H\e[2J", 11);
	printf("\033[1;36m                                         _       _  ");
	printf("     \n              _                         (_)     (_)    ");
	printf("  \n ____   ___ _| |_     ___  ___     ____  _ ____  _       ");
	printf("\n|  _ \\ / _ (_   _)   /___)/ _ \\   |    \\| |  _ \\| |     ");
	printf(" \n| | | | |_| || |_   |___ | |_| |  | | | | | | | | |  _ _ _ ");
	printf("\n|_| |_|\\___/  \\__)  (___/ \\___/   |_|_|_|_|_| |_|_| (_|_|");
	printf("_)\033[0m\n\n");
}

void	lst_env(t_data *data, char **envp)
{
	int		i;
	t_list	*new;
	t_env	*env;
	char	**line;

	i = 0;
	data->env_head = NULL;
	while (envp[i])
	{
		env = malloc(sizeof(t_env));
		if (!env)
			ft_exit(data, NULL);
		new = ft_lstnew(env);
		if (!new)
			ft_exit(data, NULL);
		line = ft_split(envp[i], '=');
		if (!line)
			ft_exit(data, NULL);
		env->id = line[0];
		env->value = line[1];
		ft_lstadd_back(&data->env_head, new);
		free(line);
		i++;
	}
}

void	del_oldpwd(t_data *data)
{
	t_list	*lst;

	lst = data->env_head;
	while (lst)
	{
		if (!ft_strcmp(((t_env *)lst->content)->id, "OLDPWD"))
		{
			free(((t_env *)lst->content)->value);
			((t_env *)lst->content)->value = NULL;
			return ;
		}
		lst = lst->next;
	}
}

void	prompt(void)
{
	write(1, "\033[1;37m", 7);
	write(1, "notsomini", 9);
	write(1, "> ", 2);
	write(1, "\033[0m", 4);
}
