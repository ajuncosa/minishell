/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:57:40 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/03/09 15:43:25 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **arg_cleaner(t_cmd *com)
{
    char    **new;
    int     i;
    int     j;

    i = 0;
    j = 0;
    new = malloc(com->n_args  * sizeof(char *)); // FIXME: he metido el tamaño a mano (para borrar "> algo") pero hay que contar cuántos vamos a borrar para poder alocar el tamaño correcto
    if (!new)
        return (NULL);
    while (i < com->n_args)
    {
        if (!ft_strncmp(com->args[i], ">", ft_strlen(com->args[i])) 
        || !ft_strncmp(com->args[i], ">>", ft_strlen(com->args[i])) 
        || !ft_strncmp(com->args[i], "<", ft_strlen(com->args[i])))
        {
            free(com->args[i]);
            free(com->args[i + 1]);
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
    new = arg_cleaner(com);
    while (i < com->n_args) // FIXME: poner el número de argumentos nuevo
    {
        printf("%s\n", new[i]);
        i++;
    }
    free(com->args);
    com->args = new;
    return(0);
}
