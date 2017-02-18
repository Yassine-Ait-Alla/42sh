/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/03 23:37:12 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:03:37 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

char	*create_good_path(t_all *all, char *cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (all->path2exec[i])
	{
		tmp = ft_strjoin(all->path2exec[i], "/");
		tmp = ft_strjoin(tmp, cmd);
		if (good_access(tmp))
			return (tmp);
		i++;
	}
	return (NULL);
}

int		check_redirect(char *s)
{
	while (*s)
	{
		if (*s == '>' || *s == '<')
			return (1);
		s++;
	}
	return (0);
}

int		open_file(char *file, int redir)
{
	int		fd;

	fd = 0;
	if (file)
	{
		if (redir == 1)
		{
			if ((fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
				write(2, "open err0r\n", 11);
		}
		else
		{
			if ((fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
				write(2, "open err0r\n", 11);
		}
	}
	return (fd);
}

char	*redirected_in_args(char **args, int *redir_type)
{
	int		i;
	char	*file_redir;

	i = 0;
	while (args[i])
	{
		if (ft_strequ(args[i], ">") || ft_strequ(args[i], ">>"))
		{
			if (ft_strequ(args[i], ">"))
				*redir_type = 1;
			else
				*redir_type = 2;
			free(args[i]);
			file_redir = args[i + 1];
			args[i] = NULL;
			args[i + 1] = NULL;
			return (file_redir);
		}
		i++;
	}
	return (NULL);
}

char	**modify_pipe_array(t_all *all, char **array)
{
	char	**modify;
	int		count;

	count = 0;
	all->redir_in_pipe = 1;
	while (array[count] && array[count][0] != '>')
		count++;
	if (!(modify = (char**)malloc(sizeof(char*) * count + 1)))
		error("MALLOC");
	count = 0;
	while (array[count] && array[count][0] != '>')
	{
		modify[count] = ft_strdup(array[count]);
		count++;
	}
	all->file2redir = ft_strdup(array[count + 1]);
	modify[count] = NULL;
	return (modify);
}
