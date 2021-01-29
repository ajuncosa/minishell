/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 11:35:29 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/01/29 11:10:45 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_commands(char *str, t_list **head, int ret, char *user)
{
	/*if (!ft_strncmp(str, "echo", 4) && (str[4] == '\n' || str[4] == ' '))		// condiciones para que si solo pones "echo" (sin espacio detrás) también entre. Si no pones las condiciones, al poner "echohola" funciona e imprime "hola" cuando debería decir command not found
		return (ft_echo(&str[4]));
	else if (!ft_strncmp(str, "pwd", 3) && (str[3] == '\n' || str[3] == ' '))
		return (ft_pwd(&str[3]));
	else if (!ft_strncmp(str, "export", 6) && (str[6] == '\n' || str[6] == ' '))
		return (ft_export(head, &str[6]));
	else if (!ft_strncmp(str, "cd", 2) && (str[2] == '\n' || str[2] == ' '))
		return (ft_cd(&str[2], user));
	else if (!ft_strncmp(str, "unset", 5) && (str[5] == '\n' || str[5] == ' '))
		return (ft_unset(head, &str[5]));
	else if (!ft_strncmp(str, "env", 3) && (str[3] == '\n' || str[3] == ' '))
		return (ft_env(head, &str[3]));
	else if (!ft_strncmp(str, "ls", 2) && (str[2] == '\n' || str[2] == ' '))
		return (ft_ls());
	else if (!ft_strncmp(str, "$?", 2) && (str[2] == '\n' || str[2] == ' '))
		return (ft_exit_status(ret));
	else if (!ft_strncmp(str, "exit", 4) && str[4] == '\n')
		return (ft_exit(head, user));
	else
	{
		write(1, "command not found\n", 18);								// possible TODO: replicar mensaje
		return (127);
	}*/
	ft_printf("command not found\n");
	return (0);
}
