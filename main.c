/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:36:03 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/04/28 12:02:13 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)		//TODO: no usamos lstnew en ningún sitio pero igual nos viene bien??? WTF
{
	int		ctrl;
	int		i;
	char	**line;
	char	*str;
	char	*oldpwd;
	t_list	*new;
	t_list	*lst;
	t_env	*env;
	size_t	user_len;
	t_data	data;

	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, quit);
	write(1, "\e[1;1H\e[2J", 11);
	printf("\033[1;36m                                         _       _       \n              _                         (_)     (_)      \n ____   ___ _| |_     ___  ___     ____  _ ____  _       \n|  _ \\ / _ (_   _)   /___)/ _ \\   |    \\| |  _ \\| |      \n| | | | |_| || |_   |___ | |_| |  | | | | | | | | |  _ _ _ \n|_| |_|\\___/  \\__)  (___/ \\___/   |_|_|_|_|_| |_|_| (_|_|_)\033[0m\n\n");
	data.cmd_head = NULL;
	user = NULL;
	i = 0;
	data.env_head = NULL;
	while (envp[i])
	{
		new = malloc(sizeof(t_list));
		if (!new)
			ft_exit(&data, NULL);
		env = malloc(sizeof(t_env));
		if (!env)
			ft_exit(&data, NULL);
		line = ft_split(envp[i], '=');
		if (!line)
			ft_exit(&data, NULL);
		new->content = env;
		((t_env *)new->content)->id = line[0];
		((t_env *)new->content)->value = line[1];
		ft_lstadd_back(&data.env_head, new);
		free(line);
		i++;
	}
	user = ft_strdup(is_in_env(&data.env_head, "USER"));
	if (!user)
	{
		user = ft_strdup("michael-s");
		if (!user)
			ft_exit(&data, NULL);
	}
	user_len = ft_strlen(user);
	lst = data.env_head;
	while (lst)
	{
		if (!ft_strcmp(((t_env *)lst->content)->id, "OLDPWD"))
		{
			free(((t_env *)lst->content)->value);
			((t_env *)lst->content)->value = NULL;
			break ;
		}
		lst = lst->next;
	}
	data.ret = 0;
	pid = -1;
	while (1)
	{
		data.line = NULL;
		write(1, "\033[1;37m", 7);
		write(1, user, user_len);
		write(1, "> ", 2);
		write(1, "\033[0m", 4);
		ctrl = get_next_line(0, &str);
		if (!ctrl)
			ctrl_d(ctrl, &str, &data);
		parser(&data, str, envp);
		free(str);
	}
	ft_exit(&data, NULL);
	return (0);
}
