/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:26:21 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/29 12:46:34 by ajuncosa         ###   ########.fr       */
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

int is_args_empty(t_cmd *com)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < com->n_args)
	{
		if (com->args[i][0] != '\0')
			j++;
		i++;
	}
	tmp = malloc(j * sizeof(char *)); //FIXME: gesttionar errores

	i = 0;
	j = 0;
	while (i < com->n_args)
	{
		if (com->args[i][0] != '\0')
		{
			tmp[j] = ft_strdup(com->args[i]);
			j++;
		}
		free(com->args[i]);
		i++;
	}
	free(com->args);
	com->args = tmp;
	com->n_args = j;
	if (com->n_args == 0)
	{
		free(com->args);
		com->args = NULL;
	}
	return (1);
}
