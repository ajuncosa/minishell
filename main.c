/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:36:03 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/01/28 13:18:57 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **envp)
{
	int		i;
	int		ret;
	char	str[1024];								//FIXME: 1024
	char	**line;
	char	*user;
	t_list	*head;
	t_list	*new;
	t_list	*lst;
	t_env	*env;
	size_t	user_len;


	write(1, "\e[1;1H\e[2J", 11);
	printf("\033[1;36m                                         _       _       \n              _                         (_)     (_)      \n ____   ___ _| |_     ___  ___     ____  _ ____  _       \n|  _ \\ / _ (_   _)   /___)/ _ \\   |    \\| |  _ \\| |      \n| | | | |_| || |_   |___ | |_| |  | | | | | | | | |  _ _ _ \n|_| |_|\\___/  \\__)  (___/ \\___/   |_|_|_|_|_| |_|_| (_|_|_)\033[0m\n\n");

	i = 0;
	head = NULL;
	while (envp[i])
	{
		new = malloc(sizeof(t_list));
		env = malloc(sizeof(t_env));
		line = ft_split(envp[i], '=');
		new->content = env;
		((t_env*)new->content)->id = line[0];
		((t_env*)new->content)->value = line[1];
		ft_lstadd_back(&head, new);
		free(line);
		i++;
	}
	lst = head;
	while (lst)
	{
		if (!ft_strncmp(((t_env*)lst->content)->id, "USER", 4))
		{	
			user_len = ft_strlen(((t_env*)lst->content)->value);
			if (!(user = ft_strdup(((t_env*)lst->content)->value)))
			{
				ft_lstclear(&head, &del_lst);
				exit(0);
			}
			break;
		}
		lst = lst->next;
	}
	ret = 0;
	while (1)
	{
		write(1, "\033[1;37m", 7);
		write(1, user, user_len);
		write(1, "> ", 2);
		write(1, "\033[0m", 4);
		read(0, str, 1023);
		ret = parse_commands(str, &head, ret, user);
		ft_bzero(str, 1023);
	}
	ft_exit(&head, user);
	return (0);
}
