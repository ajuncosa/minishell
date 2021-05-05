/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 14:01:13 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/05/05 12:33:30 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr_edit(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_complete_the_line(int fd, char **stat, char **line)
{
	int		i;
	char	*tmp;

	if (stat[fd])
	{
		i = ft_strchr_edit(stat[fd], '\n');
		if (i != -1)
		{
			*line = ft_substr(stat[fd], 0, i);
			tmp = ft_substr(stat[fd], i + 1, ft_strlen(stat[fd]) - i);
			free(stat[fd]);
			stat[fd] = tmp;
			return (1);
		}
		else
			*line = ft_substr(stat[fd], 0, ft_strlen(stat[fd]));
		free(stat[fd]);
		stat[fd] = NULL;
	}
	else
		*line = ft_strdup("");
	return (0);
}

void	alloc_stat(char **stat, size_t bytes, int fd, char *buf)
{
	char	*tmp;

	buf[bytes] = '\0';
	if (!stat[fd])
		stat[fd] = ft_strdup(buf);
	else
	{
		tmp = ft_strjoin(stat[fd], buf);
		free(stat[fd]);
		stat[fd] = tmp;
	}
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	size_t		bytes;
	static char	*stat[4096];

	buf = malloc(BUFFER_SIZE + 1);
	if (fd == -1 || !line || !buf
		|| read(fd, buf, 0) == -1 || BUFFER_SIZE <= 0)
		return (-1);
	if (!stat[fd] || ft_strchr_edit(stat[fd], '\n') == -1)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		while (bytes > 0)
		{
			alloc_stat(stat, bytes, fd, buf);
			if (ft_strchr_edit(stat[fd], '\n') != -1)
				break ;
			bytes = read(fd, buf, BUFFER_SIZE);
		}
	}
	free(buf);
	return (ft_complete_the_line(fd, stat, line));
}
