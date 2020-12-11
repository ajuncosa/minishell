/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:36:03 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/12/11 14:33:39 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		i;
	char	str[1000];

	while (1)
	{
		i = 0;
		/*while (envp[i])
		{
			if (!ft_strncmp(envp[i], "USER=", 5))	// to do: take env variables :D	
				
		}*/

		read(0, str, 999);
		if (!ft_strncmp(str, "exit", 4)) 			// to do: empty line after command :D
			exit(0);
	}
	return (0);
}
