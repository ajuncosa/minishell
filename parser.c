/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 11:35:29 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/12/22 11:55:48 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_commands(char *str, t_list *head)
{
	if (!ft_strncmp(str, "echo", 4) && (str[4] == '\n' || str[4] == ' '))		// condiciones para que si solo pones "echo" (sin espacio detrás) también entre. Si no pones las condiciones, al poner "echohola" funciona e imprime "hola" cuando debería decir command not found
		ft_echo(&str[4]);
	/*else if (!ft_strncmp(str, "cd", 2))
	else if (!ft_strncmp(str, "pwd", 3))
	else if (!ft_strncmp(str, "export", 6))
	else if (!ft_strncmp(str, "unset", 5))*/
	else if (!ft_strncmp(str, "env", 3))
		ft_env(head);
	else if (!ft_strncmp(str, "exit", 4)) 										// TODO: check if line is empty after command :D
		ft_exit(&head);
	else
		write(1, "Command not found\n", 18);
}
