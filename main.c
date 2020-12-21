/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:36:03 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/12/21 14:04:30 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **envp)
{
	int		i;
	char	str[1024];
	t_list	*head;
	t_list	*new;
	t_env	*env;
	char	**line;
	t_list	*lst;
	char	*user;
	size_t	user_len;

	printf("\033[1;36m                                         _       _       \n              _                         (_)     (_)      \n ____   ___ _| |_     ___  ___     ____  _ ____  _       \n|  _ \\ / _ (_   _)   /___)/ _ \\   |    \\| |  _ \\| |      \n| | | | |_| || |_   |___ | |_| |  | | | | | | | | |  _ _ _ \n|_| |_|\\___/  \\__)  (___/ \\___/   |_|_|_|_|_| |_|_| (_|_|_)\033[0m\n\n");

	i = 0;
	head = NULL;
	while (envp[i])																	// FIXME: leaks
	{
		new = malloc(sizeof(t_list));
		env = malloc(sizeof(t_env));
		line = ft_split(envp[i], '=');
		new->content = env;
		((t_env*)new->content)->id = line[0];
		((t_env*)new->content)->value = line[1];
		ft_lstadd_back(&head, new);
		i++;
	}
	lst = head;
	while (lst)
	{
		if (!ft_strncmp(((t_env*)lst->content)->id, "USER", 4))
		{
			user = ((t_env*)lst->content)->value;
			user_len = ft_strlen(user);
		}
		lst = lst->next;
	}
	while (1)
	{
		write(1, "\033[1;37m", 7);
		write(1, user, user_len);
		write(1, "> ", 2);
		write(1, "\033[0m", 4);
		read(0, str, 1023);
		if (!ft_strncmp(str, "echo", 4) && (str[4] == '\n' || str[4] == ' '))		// condiciones para que si solo pones "echo" (sin espacio detrás) también entre. Si no pones las condiciones, al poner "echohola" funciona e imprime "hola" cuando debería decir command not found
			ft_echo(&str[4]);
		else if (!ft_strncmp(str, "env", 3))
			ft_env(head);
		else if (!ft_strncmp(str, "exit", 4)) 										// TODO: check if line is empty after command :D
			ft_exit(&head);
		else
			write(1, "Command not found\n", 18);		
		ft_bzero(str, 1023);
	}
	ft_exit(&head);
	return (0);
}
