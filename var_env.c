/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:30:58 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/03/25 18:38:16 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_in_env(t_list **env_head, char *str)  //TODO: esto se puede usar en más sitios
{
	t_list *list;

	list = *env_head;
	while (list)
	{
		if (!ft_strcmp(str, ((t_env*)list->content)->id))
			return (((t_env*)list->content)->value);
		list = list->next;
	}
	return (NULL);
}

int	dollar_finder(t_list **env_head, char **str)
{
	int		start;
	int		end;
	char	*check;
	char	*value;
	char 	*tmp;
	char	*tmp2;
	char	*tmp3;

	start = 0;
	while ((*str)[start] != '\0')
	{
		if ((*str)[start] == '$')
		{
			start++;
			end = start;
			while ((*str)[end] != ' ' && (*str)[end] != '"' && (*str)[end] != '\''
			&& (*str)[end] != '>' && (*str)[end] != '<' && (*str)[end] != '\n'
			&& (*str)[end] != ';' && (*str)[end] != '|' && (*str)[end] != '\0')
				end++;

			check = ft_substr(*str, start, end - start); // TODO: gestionar errores en todas estas
			value = is_in_env(env_head, check);
			if (value)
			{
				tmp = ft_substr(*str, 0, start - 1);
				tmp2 = ft_strjoin(tmp, value);
				tmp3 = ft_strjoin(tmp2, &(*str)[end]);
				free(*str);
				*str = tmp3;
				//printf("tmp: |%s| valor: |%s|\n", tmp, value);
				//printf("|%s|\n", *str);
				//printf("&str[end]: |%s|\n", &str[end]);
				free(check);
				free(tmp);
				free(tmp2);
			}
		}
		start++;
	}
	return (1); // TODO: valores de retorno
}
