/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:06:51 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/04/30 20:24:20 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_path(t_data *data)
{
	char		**paths;
	t_list		*lst;

	lst = data->env_head;
	while (lst)
	{
		if (!ft_strcmp(((t_env *)lst->content)->id, "PATH"))
		{
			if (((t_env *)lst->content)->value)
			{
				paths = ft_split(((t_env *)lst->content)->value, ':');
				if (!paths)
					ft_exit(data, NULL);
			}
			break ;
		}
		lst = lst->next;
	}
	return (paths);
}

char	*is_in_path(char **paths, char *cmd, t_data *data, int *i)
{
	char		*joined;
	char		*tmp;
	struct stat	stat;

	tmp = ft_strjoin(paths[*i], "/");
	if (!tmp)
		ft_exit(data, NULL);
	joined = ft_strjoin(tmp, cmd);
	if (!joined)
		ft_exit(data, NULL);
	free(tmp);
	lstat(joined, &stat);
	if (S_ISREG(stat.st_mode))
	{
		free_str_array(paths);
		return (joined);
	}
	free(joined);
	return (NULL);
}

char	*ft_pathfinder(char *cmd, t_data *data)
{
	int		i;
	char	*joined;
	char	**paths;

	paths = NULL;
	paths = fill_path(data);
	if (paths)
	{
		i = 0;
		while (paths[i])
		{
			joined = is_in_path(paths, cmd, data, &i);
			if (joined)
				return (joined);
			i++;
		}
		free_str_array(paths);
	}
	return (NULL);
}
