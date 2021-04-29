/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:06:51 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/04/29 20:17:28 by cruiz-de         ###   ########.fr       */
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

char	*ft_pathfinder(char *cmd, t_data *data)
{
	char		**paths;
	char		*joined;
	char		*tmp;
	int			i;
	struct stat	stat;

	paths = NULL;
	paths = fill_path(data);
	if (paths)
	{
		i = 0;
		while (paths[i])
		{
			tmp = ft_strjoin(paths[i], "/");
			if (!tmp)
				ft_exit(data, NULL);
			joined = ft_strjoin(tmp, cmd);
			if (!joined)
				ft_exit(data, NULL);
			free(tmp);
			lstat(joined, &stat);
			if (S_ISREG(stat.st_mode))
			{
				i = 0;
				while (paths[i])
				{
					free(paths[i]);
					i++;
				}
				free(paths);
				return (joined);
			}
			free(joined);
			i++;
		}
		i = 0;
		while (paths[i])
		{
			free(paths[i]);
			i++;
		}
		free(paths);
	}
	return (NULL);
}
