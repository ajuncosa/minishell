/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:30:58 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/04/16 11:47:26 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_finder(t_list **env_head, char **str, int ret)	//TODO: probar si echo $PW\D hace lo que tiene que hacer
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
			if ((*str)[start] == ' ' || (*str)[start] == '\0')
				return (1);
			while (ft_isalnum((*str)[end]) || (*str)[end] == '_')
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
			start -= 2;		//TODO: checkear si esto me ha roto algo en estas envs
		}
		start++;
	}
	return (1);
}
