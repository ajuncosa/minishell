/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:36:03 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/04/22 13:30:24 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void quit(int sig)
{
	if (pid == -1)
	{
		write(1, "\b\b", 2); // move cursor behind of ^C
		write(1, "  ", 2); // remove ^C by printing spaces.
		write(1, "\b\b", 2); // reset cursor pos
	}
	else if (pid > 0)
		write(1, "Quit: 3\n", 8);
}

void ctrl_c(int sig)	//FIXME: si ejecutas la minishell dentro de la minishell, todo esto funciona mal :(
{
	if (pid == -1)
	{
		write(1, "\b\b", 2); // move cursor behind of ^C
		write(1, "  ", 2); // remove ^C by printing spaces.
		write(1, "\b\b", 2); // reset cursor pos
		write(1, "\n\033[1;37m", 9);
		write(1, user, ft_strlen(user));
		write(1, "> ", 2);
		write(1, "\033[0m", 4);
	}
	else if (pid > 0)
		write(1, "\n", 1);
}

int		main(int argc, char **argv, char **envp)		//TODO: no usamos lstnew en ningún sitio pero igual nos viene bien??? WTF
{
	int		ctrl;
	int		i;
	//int		ret;
	//char	str[1024];								//FIXME: 1024
	char	**line;
	char	*str;
	//char	*user;
	char	*oldpwd;
	//t_list	*head;
	t_list	*new;
	t_list	*lst;
	t_env	*env;
	size_t	user_len;
	char	*tmp;
	t_data	data;		//TODO: a lo mejor queremos cambiar todos los returns y utilizar el data.ret en todas las funciones?? se podría??


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
		if (!(new = malloc(sizeof(t_list))))
			ft_exit(&data, NULL);
		if (!(env = malloc(sizeof(t_env))))
			ft_exit(&data, NULL);
		if (!(line = ft_split(envp[i], '=')))
			ft_exit(&data, NULL);
		new->content = env;
		((t_env*)new->content)->id = line[0];
		((t_env*)new->content)->value = line[1];
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
		if (!ft_strcmp(((t_env*)lst->content)->id, "OLDPWD"))
		{
			free(((t_env*)lst->content)->value);
			((t_env*)lst->content)->value = NULL;
			break;
		}
		lst = lst->next;
	}

	data.ret = 0;
	pid = -1;
	while (1)
	{
		write(1, "\033[1;37m", 7);
		write(1, user, user_len);
		write(1, "> ", 2);
		write(1, "\033[0m", 4);
		ctrl = get_next_line(0, &str);	//TODO: revisar buffersize??
		parser(&data, str, envp);
		if (!ctrl && str[0] == '\0')			 //FIXME: no funciona
		{
			free(str);
			ft_exit(&data, NULL);
		}
		free(str);
	}
	ft_exit(&data, NULL);
	return (0);
}
