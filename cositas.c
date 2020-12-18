
// para multiline en el echo
char	*dquote(char *str)
{
	char	dquo[1024];
	char	*joined;
	char 	*final;

	write(1, "dquote> ", 9);
	read(0, dquo, 1023);
	joined = ft_strjoin(str, dquo);
	if (!ft_strchr(dquo, '"'))
		final = dquote(joined);
	else
		final = ft_strdup(joined);
	free(joined);
	return(final);
}

// esto de abajo estaba en echo dentro del if de si no encontraba las "" de cerrar
/*
    	char *seg;
				seg = dquote(&str[i]);									// dquote devuelve un char * con todo lo que viene después de una coma que se queda abierta
				end = 0;
				while (seg[end] != '"')
					end++;
				write(1, seg, end);										// imprime lo que hay en seg hasta que se cierren las " que estaban abiertas
				end += 2;												// para saltarme las " y el \n
				if (seg[end] != '\0')
					echo(&seg[end], 2);									// hace cosas muy raras x ejjemplo si haces varios echos con comillas abiertas seguidos
				free(seg);
				break;
*/