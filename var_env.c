/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:30:58 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/03/26 15:15:02 by ajuncosa         ###   ########.fr       */
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

int	dollar_finder(t_list **env_head, char **str, int ret)
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
			&& (*str)[end] != '$'
			&& (*str)[end] != '>' && (*str)[end] != '<' && (*str)[end] != '\n'
			&& (*str)[end] != ';' && (*str)[end] != '|' && (*str)[end] != '\0')
				end++;

			check = ft_substr(*str, start, end - start);
			if (!check)
				return (0);
			value = is_in_env(env_head, check);
			if (!value && (*str)[start] == '?')
			{
				value = ft_itoa(ret);
				if (!value)
					return (0);
			}
			if (value)
			{
				tmp = ft_substr(*str, 0, start - 1);
				if (!tmp)
					return (0);
				tmp2 = ft_strjoin(tmp, value);
				if (!tmp2)
					return (0);
				tmp3 = ft_strjoin(tmp2, &(*str)[end]);
				if (!tmp3)
					return (0);
				if ((*str)[start] == '?')
					free(value);
				free(*str);
				*str = tmp3;
				free(tmp);
				free(tmp2);
			}
			else
			{
				tmp = ft_substr(*str, 0, start - 1);
				if (!tmp)
					return (0);
				tmp2 = ft_strjoin(tmp, &(*str)[end]);
				if (!tmp2)
					return (0);
				free(*str);
				*str = tmp2;
				free(tmp);
			}
			free(check);
			start--;
		}
		start++;
	}
	return (1);
}
