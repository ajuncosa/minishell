/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 12:09:58 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/01/29 12:58:38 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_ls(void)
{
    struct dirent   *p_dirent;
    DIR             *pdir;
    char            *buf;

    buf = NULL;
	buf = getcwd(buf, 0);
    pdir = opendir(buf);
    if (pdir == NULL) 
    {
        printf ("Cannot open directory\n");
        return (1);
    }
    while ((p_dirent = readdir(pdir)) != NULL)
    {
        write(1, p_dirent->d_name, ft_strlen(p_dirent->d_name));
        write(1, "    ", 4);
    }
    write(1, "\n", 1);
    closedir(pdir);
    free(buf);
    return (0);
}
