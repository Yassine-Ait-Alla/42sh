/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 16:18:31 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 11:05:32 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int					hasher(t_shell *shell, int fdout)
{
	t_hash				*temp;

	temp = shell->hash;
	while (temp)
	{
		if (temp->time)
		{
			ft_putnbr_fd(temp->time, fdout);
			ft_putchar_fd(' ', fdout);
			putcolor(temp->path, DEFAULT, fdout, 1);
		}
		temp = temp->next;
	}
	return (0);
}

static void			env_up(t_shell **shell)
{
	char				*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	free((*shell)->old_pwd);
	(*shell)->old_pwd = ft_strdup((*shell)->pwd);
	free((*shell)->pwd);
	(*shell)->pwd = pwd;
	seter("OLDPWD", (*shell)->old_pwd, shell);
	seter("PWD", (*shell)->pwd, shell);
}

static int			change_dir(t_shell **shell, char *path, char *arg)
{
	if (access(path, F_OK) == 0)
	{
		if (cd_error(path, arg) == 0)
		{
			chdir(path);
			env_up(shell);
			return (0);
		}
		else
			return (1);
	}
	else
	{
		putcolor("cd: no such file or directory: ", DEFAULT, 2, 0);
		putcolor(arg, MAGENTA, 2, 1);
		return (1);
	}
}

int					ft_cd(t_shell **shell, char **arg)
{
	char				*path;
	int					ret;

	if (ft_tablen(arg) == 1)
		path = ft_strdup((*shell)->home);
	else if (recurcmp(arg[1], "-") == 0)
		path = ft_strdup((*shell)->old_pwd);
	else
	{
		if (arg[1][0] == '/')
			path = ft_strdup(arg[1]);
		else
		{
			path = (char *)ft_memalloc(ft_strlen((*shell)->pwd) +
							ft_strlen(arg[1]) + 2);
			ft_strcat(path, (*shell)->pwd);
			ft_strcat(path, "/");
			ft_strcat(path, arg[1]);
		}
	}
	ret = change_dir(shell, path, arg[1]);
	free(path);
	return (ret);
}

int					built(char **arg, t_shell *shell, int fdout, int i)
{
	if (recurcmp(arg[0], "exit") == 0)
		ft_exit(&shell, arg);
	if (recurcmp(arg[0], "hist") == 0)
		STATUS = display_historic(shell, arg);
	if (recurcmp(arg[0], "cd") == 0)
		STATUS = ft_cd(&shell, arg);
	else if (ft_strncmp(arg[0], "<<", 2) == 0)
		STATUS = heredoc(shell, arg);
	else if (recurcmp(arg[0], "prompt") == 0)
		STATUS = change_prompt(shell);
	else if (recurcmp(arg[0], "color") == 0)
		STATUS = change_color(shell, arg);
	else if (recurcmp(arg[0], "env") == 0)
		STATUS = ft_env(shell, fdout);
	else if (recurcmp(arg[0], "hash") == 0)
		STATUS = hasher(shell, fdout);
	else if (recurcmp(arg[0], "unsetenv") == 0)
		STATUS = check_env(arg, &shell, 2);
	else if (recurcmp(arg[0], "setenv") == 0)
		STATUS = check_env(arg, &shell, 1);
	if (i == 0)
		exit(STATUS);
	return (STATUS);
}
