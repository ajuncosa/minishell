/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:57:40 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/03/10 14:16:52 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **arg_cleaner(t_cmd *com, t_redir *redir) //FIXME: hacer frees de redir, redir[i] y del contenido de cada uno
{
    char    **new;
    int     i;
    int     j;
    int     k;
    int     n_del;
    //contar nargs a borrar
    i = 0;
    n_del = 0;
    while (i < com->n_args)
    {
        if (!ft_strncmp(com->args[i], ">", ft_strlen(com->args[i])) 
        || !ft_strncmp(com->args[i], ">>", ft_strlen(com->args[i])) 
        || !ft_strncmp(com->args[i], "<", ft_strlen(com->args[i])))
            n_del += 2;
        i++;
    }
    com->n_redir = n_del / 2;
    //crear nueva string y array de redirs
    new = malloc((com->n_args - n_del)  * sizeof(char *));
    if (!new)
        return (NULL);
    redir = malloc(com->n_redir * sizeof(t_redir));
    if (!redir)
        return (NULL);
    /*i = 0;
    while (i < com->n_redir)
    {
        redir[i] = malloc(sizeof(t_redir));
        if (!redir[i])
            return (NULL);
        i++;
    }
    */
    i = 0;
    j = 0;
    k = 0;
    while (i < com->n_args)
    {
        if (!ft_strncmp(com->args[i], ">", ft_strlen(com->args[i])) 
        || !ft_strncmp(com->args[i], ">>", ft_strlen(com->args[i])) 
        || !ft_strncmp(com->args[i], "<", ft_strlen(com->args[i])))
        {
            free(com->args[i]);
            free(com->args[i + 1]);
            redir[k].type = ft_strdup(com->args[i]);
            if (!redir[k].type)
                return (NULL);
            redir[k].file = ft_strdup(com->args[i + 1]);
            if (!redir[k].file)
                return (NULL);
            k++;
            i++;
        }
        else 
        {
            new[j] = ft_strdup(com->args[i]);
            if (!new[j])
                return(NULL);
            j++;
        }
        i++;
    }
    com->n_args = com->n_args - n_del;
    return(new);
}

int redir_manager(t_cmd *com)
{
    char    **new;
    int     i;
    t_redir *redir;
   // int     fd;
    //int     pid;

    i = 0;
    /*while (i < com->n_args)
    {
        if (!ft_strncmp(com->args[i], ">", ft_strlen(com->args[i])))
        {
            pid = fork();
            if (pid == 0)
            {
                fd = open(com->args[i + 1], O_WRONLY, O_CREAT);
                dup2(fd, STDOUT_FILENO);
                r = cmd_caller(com, );
            }
        }
        i++;
    }  */

    new = arg_cleaner(com, redir);
    while(i < com->n_redir)
    {
        printf("%s, %s\n", redir[i].type, redir[i].file);
        i++;
    }
    free(com->args);
    com->args = new;
    return(0);
}
