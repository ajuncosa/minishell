/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:57:40 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/03/09 13:49:57 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **arg_cleaner(char **args)
{
    char **new;
    int i;
    int j;

    i = 0;
    j = 0;
    while (args[i] != NULL)
    {
        if (!ft_strncmp(args[i], ">", ft_strlen(args[i])) 
        || !ft_strncmp(args[i], ">>", ft_strlen(args[i])) 
        || !ft_strncmp(args[i], "<", ft_strlen(args[i])))
        {
            free(args[i]);
            free(args[i + 1]);
        }
        else 
        {
            new[j] = ft_strdup(args[i]);
            if (!new[j])
                return(NULL);
            j++;
        }
        i++;
    }   
    return(new);
}

int redir_manager(t_cmd *com)
{
    char **new;
    int i;

    i = 0;
    /*while (i < com->n_args)
    {
        if (!ft_strncmp(com->args[i], ">", ft_strlen(com->args[i])))
        {
            
        }
        i++;
    }   */
    new = arg_cleaner(com->args);
    while (new[i])
    {
        printf("%s\n", new[i]);
        i++;
    }
    return(0);
}
