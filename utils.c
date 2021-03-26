/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:26:21 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/26 18:22:18 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space_quote_redir_or_endofcmd(char c)
{
	if (c == ' ' || c == '"' || c == '\'' || c == '<' || c == '>' 
		|| c == '\n' || c == ';' || c == '|' || c == '\0')
		return (1);
	else
		return (0);
}

int	is_space_redir_or_endofcmd(char c)
{
	if (c == ' ' || c == '<' || c == '>' || c == '\n'
		|| c == ';' || c == '|' || c == '\0')
		return (1);
	else
		return (0);
}
