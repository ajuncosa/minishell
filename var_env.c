/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:30:58 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/04/15 14:48:05 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			while (ft_isalnum((*str)[end]) || (*str)[end] == '_')
				end++;
			if (end == start)
				return (1);
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
			start -= 2;		//TODO: checkear si esto me ha roto algo en estas envs
		}
		start++;
	}
	return (1);
}
