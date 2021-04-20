
t_letter	*str_to_struct(char *str)
{
	int			i;
	int			j;
	int			len;
	int			quote;
	t_letter	*line;

	i = 0;
	j = 0;
	quote = 0;
	len = esc_size(str);
	line = malloc((len + 1) * sizeof(t_letter));
	if (!line)
		return (NULL);
	while (str[i])		//TODO: error open "\"
	{
		if (str[i] == '\'')
		{
			if (!quote)
				quote = 1;
			else
				quote = 0;
		}
		line[j].esc = 0;
		if (str[i] == '\\' && !quote)
		{
			i++;
			line[j].esc = 1;
		}
		line[j].c = str[i];
		i++;
		j++;
	}
	line[j].c = '\0';
	return (line);
	/*i = 0;
	while (i < len)
	{
		printf("str: %c esc: %d\n", line[i].c, line[i].esc);
		i++;
	}
	*/
}



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

//recursividad para los pipes, la intencion es lo que cuenta!
void	rec_pipe(t_list *lst, int fd_read)
{
	int	pid;
	int	fd_new[2];

	if (((t_cmd*)lst->content)->sep_1 == '|')
	{
		pipe(fd_new);
		pid = fork();
		if (pid == 0)
		{
			if (((t_cmd*)lst->content)->sep_0 == '|')
				dup2(fd_read, STDIN_FILENO);
			close(fd_read);
			close(fd_new[0]);
			dup2(fd_new[1], STDOUT_FILENO);
			close(fd_new[1]);
			if (!strncmp(((t_cmd*)lst->content)->cmd, "pwd", 4))
				ft_pwd(((t_cmd*)lst->content)->cmd, ((t_cmd*)lst->content)->args); //TODO: returns
			else
				ft_cmd(((t_cmd*)lst->content)->cmd);
			exit(0);
		}
		wait(NULL);
		close(fd_new[1]);
		rec_pipe(lst->next, fd_new[0]);
		close(fd_new[0]);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(fd_read, STDIN_FILENO);
			close(fd_read);
			if (!strncmp(((t_cmd*)lst->content)->cmd, "pwd", 4))
				ft_pwd(((t_cmd*)lst->content)->cmd, ((t_cmd*)lst->content)->args); //TODO: returns
			else
				ft_cmd(((t_cmd*)lst->content)->cmd);
			exit(0);
		}
		wait(NULL);
	}
	close(fd_read);
}