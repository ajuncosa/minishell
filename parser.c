/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 11:35:29 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/01/28 12:25:35 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_commands(char *str, t_list **head, char *user)
{
	if (!ft_strncmp(str, "echo", 4) && (str[4] == '\n' || str[4] == ' '))		// condiciones para que si solo pones "echo" (sin espacio detrás) también entre. Si no pones las condiciones, al poner "echohola" funciona e imprime "hola" cuando debería decir command not found
		ft_echo(&str[4]);
	else if (!ft_strncmp(str, "pwd", 3) && (str[3] == '\n' || str[3] == ' '))
		ft_pwd(&str[3]);
	else if (!ft_strncmp(str, "export", 6) && (str[6] == '\n' || str[6] == ' '))
		ft_export(head, &str[6]);
	else if (!ft_strncmp(str, "cd", 2) && (str[2] == '\n' || str[2] == ' '))
		ft_cd(&str[2], user);
	else if (!ft_strncmp(str, "unset", 5) && (str[5] == '\n' || str[5] == ' '))
		ft_unset(head, &str[5]);
	else if (!ft_strncmp(str, "env", 3) && (str[3] == '\n' || str[3] == ' '))
		ft_env(head, &str[3]);
	else if (!ft_strncmp(str, "ls", 2) && (str[2] == '\n' || str[2] == ' '))
		ft_ls();
	else if (!ft_strncmp(str, "exit", 4) && str[4] == '\n')
		ft_exit(head, user);
	else
		write(1, "command not found\n", 18);									// possible TODO: replicar mensaje
}
