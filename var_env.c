/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:30:58 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/05/03 13:45:10 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_novalue(t_letter **str, int start, int end)
{
	t_letter	*tmp1;
	t_letter	*tmp2;

	tmp1 = esc_substr(*str, 0, start - 1);
	if (!tmp1)
		return (0);
	tmp2 = esc_join(tmp1, &(*str)[end]);
	if (!tmp2)
		return (0);
	free(*str);
	*str = tmp2;
	free(tmp1);
	return (1);
}

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

int	find_value(t_letter *str, char **value, int ret, t_list **env_head)
{
	int		i;
	char	*check;

	i = 0;
	while ((ft_isalnum(str[i].c) || str[i].c == '_') && !str[i].esc)
		i++;
	check = struct_to_str(str, 0, i);
	if (!check)
		return (-1);
	if (str[0].c == '?')
	{
		*value = ft_itoa(ret);
		i++;
		if (!*value)
			return (-1);
	}
	else
		*value = is_in_env(env_head, check);
	free(check);
	return (i);
}

int	check_value(char *value, t_letter **str, int start, int end)
{
	if (value)
	{
		if (!replace_value(value, str, start, end))
			return (0);
	}
	else
	{
		if (!replace_novalue(str, start, end))
			return (0);
	}
	return (1);
}

int	dollar_finder(t_list **env_head, t_letter **str, int ret)
{
	char	*value;
	int		start;
	int		end;
	int		r;

	start = 0;
	while ((*str)[start].c != '\0')
	{
		if ((*str)[start].c == '$' && !(*str)[start].esc)
		{
			start++;
			if ((*str)[start].c == ' ' || (*str)[start].c == '\0')
				continue ;
			r = find_value(&(*str)[start], &value, ret, env_head);
			if (r == -1)
				return (0);
			end = start + r;
			if (!check_value(value, str, start, end))
				return (0);
			start -= 2;
		}
		start++;
	}
	return (1);
}
