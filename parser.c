/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 11:35:29 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/02/16 11:37:27 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_commands(char *str, t_list **head, int ret, char *user)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (!ft_strncmp(&str[i], "echo", 4) && (str[i + 4] == '\n' || str[i + 4] == ' '))		// condiciones para que si solo pones "echo" (sin espacio detrás) también entre. Si no pones las condiciones, al poner "echohola" funciona e imprime "hola" cuando debería decir command not found
		return (ft_echo(&str[i + 4]));
	else if (!ft_strncmp(&str[i], "pwd", 3) && (str[i + 3] == '\n' || str[i + 3] == ' '))
		return (ft_pwd(&str[i + 3]));
	else if (!ft_strncmp(&str[i], "export", 6) && (str[i + 6] == '\n' || str[i + 6] == ' '))
		return (ft_export(head, &str[i + 6]));
	else if (!ft_strncmp(&str[i], "cd", 2) && (str[i + 2] == '\n' || str[i + 2] == ' '))
		return (ft_cd(&str[i + 2], user));
	else if (!ft_strncmp(&str[i], "unset", 5) && (str[i + 5] == '\n' || str[i + 5] == ' '))
		return (ft_unset(head, &str[i + 5]));
	else if (!ft_strncmp(&str[i], "env", 3) && (str[i + 3] == '\n' || str[i + 3] == ' '))
		return (ft_env(head, &str[i + 3]));
	else if (!ft_strncmp(&str[i], "$?", 2) && (str[i + 2] == '\n' || str[i + 2] == ' '))
		return (ft_exit_status(ret));
	else if (!ft_strncmp(&str[i], "exit", 4) && (str[i + 4] == '\n'|| str[i + 4] == ' '))
		ft_exit(head, user);
	else
		return (ft_cmd(&str[i]));
	return (0);
}
