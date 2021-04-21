/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:30:58 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/04/21 16:27:59 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_finder(t_list **env_head, t_letter **str, int ret)	//TODO: probar si echo $PW\D hace lo que tiene que hacer
{		//TODO: checkear si los frees están bien
	int			start;
	int			end;
	char		*check;
	char		*value;
	t_letter	*struct_val;
	t_letter 	*tmp1;
	t_letter	*tmp2;

	start = 0;
	while ((*str)[start].c != '\0')
	{
		if ((*str)[start].c == '$')
		{
			start++;
			end = start;
			if ((*str)[start].c == ' ' || (*str)[start].c == '\0')
				return (1);
			while (ft_isalnum((*str)[end].c) || (*str)[end].c == '_')
				end++;
			check = struct_to_str(*str, start, end - start);
			if (!check)
				return (0);
			if ((*str)[start].c == '?')
			{
				value = ft_itoa(ret);
				if (!value)
					return (0);
			}
			else
				value = is_in_env(env_head, check);
			free(check);
			struct_val = str_to_struct(value);
			if (!struct_val)	// FIXME: si value era null porque no lo había encontrado, struct_val va a salirse aquí e igual eso no es lo que queremos; pero necesitamos gestionar posible error de malloc
				return (0);
			if (value)
			{

				int i = 0;
				while (struct_val[i].c != '\0')
				{
					printf("struc: |%c|\n", struct_val[i].c);
					i++;
				}

				tmp1 = esc_substr(*str, 0, start - 1);	// FIXME: FIXME: FIXME: POR AlGUn MOTIVO SE ROMPE STRUCT_VAL AL LLEGAR AQUÍ WTFFFF
				if (!tmp1)
					return (0);

				tmp2 = esc_join(tmp1, struct_val);


				/*i = 0;
				while (tmp2[i].c != '\0')
				{
					printf("join: |%c|\n", tmp2[i].c);
					i++;
				}*/

				
				if (!tmp2)
					return (0);
				free(tmp1);
				tmp1 = esc_join(tmp2, &(*str)[end]);
				if (!tmp1)
					return (0);
				if ((*str)[start].c == '?')
					free(value);
				free(*str);
				*str = tmp1;
				free(tmp2);
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
			free(struct_val);
			start -= 2;		//TODO: checkear si esto me ha roto algo en estas envs
		}
		start++;
	}
	return (1);
}
