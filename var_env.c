/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:30:58 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/05/03 11:26:12 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_value(char *value, t_letter **str, int start, int end)
{
	t_letter	*tmp1;
	t_letter	*tmp2;
	t_letter	*tmp3;
	t_letter	*struct_val;

	struct_val = str_to_struct(value);
	if (!struct_val)
		return (0);
	tmp1 = esc_substr(*str, 0, start - 1);
	if (!tmp1)
		return (0);
	tmp2 = esc_join(tmp1, struct_val);
	if (!tmp2)
		return (0);
	tmp3 = esc_join(tmp2, &(*str)[end]);
	if (!tmp3)
		return (0);
	if ((*str)[start].c == '?')
		free(value);
	free(*str);
	*str = tmp3;
	free(tmp1);
	free(tmp2);
	free(struct_val);
	return (1);
}

int	dollar_finder(t_list **env_head, t_letter **str, int ret)
{
	int			start;
	int			end;
	char		*check;
	char		*value;
	t_letter	*tmp1;
	t_letter	*tmp2;
	t_letter	*tmp3;

	start = 0;
	while ((*str)[start].c != '\0')
	{
		if ((*str)[start].c == '$' && !(*str)[start].esc)
		{
			start++;
			end = start;
			if ((*str)[start].c == ' ' || (*str)[start].c == '\0')
				continue ;
			while ((ft_isalnum((*str)[end].c) || (*str)[end].c == '_') && !(*str)[end].esc)
				end++;
			check = struct_to_str(*str, start, end - start);
			if (!check)
				return (0);
			if ((*str)[start].c == '?')
			{
				value = ft_itoa(ret);
				end++;
				if (!value)
					return (0);
			}
			else
				value = is_in_env(env_head, check);
			free(check);
			if (value)
			{
				if (!replace_value(value, str, start, end))
					return (0);
			}
			else
			{
				tmp1 = esc_substr(*str, 0, start - 1);
				if (!tmp1)
					return (0);
				tmp2 = esc_join(tmp1, &(*str)[end]);
				if (!tmp2)
					return (0);
				free(*str);
				*str = tmp2;
				free(tmp1);
			}
			start -= 2;
		}
		start++;
	}
	return (1);
}
