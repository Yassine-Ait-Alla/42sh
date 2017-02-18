/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 16:08:32 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 11:20:04 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void				init(t_shell *shell)
{
	shell->hash = NULL;
	shell->ast = NULL;
	shell->token = NULL;
	HST = (t_hist *)malloc(sizeof(t_hist));
	HST->hist = (char **)malloc(sizeof(char *) * 101);
	HST->len = 0;
	HST->ok = 0;
	HST->index = 0;
	SET.prompt = 2;
	SET.test = 0;
	SET.cursor = 0;
	SET.cmdlen = 0;
	SET.pos = 15;
	SET.prompt_len = 14;
	SET.line = 1;
	SET.max = 1;
	shell->builtin[0] = ft_strdup("cd");
	shell->builtin[1] = ft_strdup("env");
	shell->builtin[2] = ft_strdup("setenv");
	shell->builtin[3] = ft_strdup("unsetenv");
	shell->builtin[4] = ft_strdup("hash");
	shell->builtin[5] = ft_strdup("exit");
	shell->builtin[6] = ft_strdup("hist");
	shell->builtin[7] = ft_strdup("color");
	shell->builtin[8] = ft_strdup("prompt");
}

static void				ft_hash(t_shell *shell)
{
	char					**path_tab;
	int						i;
	DIR						*dir;
	struct dirent			*d;

	if (shell->path)
	{
		path_tab = ft_strsplit(shell->path, ':');
		i = 0;
		while (path_tab[i])
		{
			if ((dir = opendir(path_tab[i])) != NULL)
			{
				while ((d = readdir(dir)) != NULL)
				{
					if (d->d_name[0] != '.')
						recup(&(shell->hash), d->d_name, path_tab[i]);
				}
				closedir(dir);
			}
			free(path_tab[i]);
			i++;
		}
		free(path_tab);
	}
}

static void				no_env(t_shell *shell)
{
	SET.no_env = 1;
	shell->env = (char **)malloc(sizeof(char *) * 7);
	shell->pwd = getcwd(NULL, 0);
	shell->env[0] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/usr/local/bin");
	shell->path = ft_strdup(&(shell->env[0][5]));
	shell->env[1] = ft_strnew(ft_strlen(shell->pwd) + 4);
	ft_strcat(shell->env[1], "PWD=");
	ft_strcat(shell->env[1], shell->pwd);
	shell->old_pwd = ft_strdup(shell->pwd);
	shell->env[2] = ft_strnew(ft_strlen(shell->old_pwd) + 7);
	ft_strcat(shell->env[2], "OLDPWD=");
	ft_strcat(shell->env[2], shell->old_pwd);
	shell->home = ft_strdup(shell->pwd);
	shell->env[3] = ft_strnew(ft_strlen(shell->home) + 5);
	ft_strcat(shell->env[3], "HOME=");
	ft_strcat(shell->env[3], shell->home);
	shell->env[4] = ft_strdup("TERM=xterm-256color");
	shell->env[5] = ft_strdup("_=/usr/bin/env");
	shell->env[6] = NULL;
}

static void				init_shell(t_shell *shell, char **environ)
{
	int						i;

	if (ft_tablen(environ) < 5)
	{
		no_env(shell);
		return ;
	}
	i = -1;
	shell->env = (char **)malloc(sizeof(char *) * (ft_tablen(environ) + 1));
	while (environ[++i])
		shell->env[i] = ft_strdup(environ[i]);
	shell->env[i] = NULL;
	i = -1;
	while (shell->env[++i])
	{
		if (ft_strncmp(shell->env[i], "PATH=", 5) == 0)
			shell->path = ft_strdup(&(shell->env[i][5]));
		if (ft_strncmp(shell->env[i], "PWD=", 4) == 0)
			shell->pwd = ft_strdup(&(shell->env[i][4]));
		if (ft_strncmp(shell->env[i], "OLDPWD=", 7) == 0)
			shell->old_pwd = ft_strdup(&(shell->env[i][7]));
		if (ft_strncmp(shell->env[i], "HOME=", 5) == 0)
			shell->home = ft_strdup(&(shell->env[i][5]));
	}
}

t_shell					*init_all(char **environ)
{
	t_shell					*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	init(shell);
	shell->heredoc = 0;
	shell->test = -1;
	shell->status = 0;
	shell->EOM = NULL;
	SET.no_env = 0;
	SET.close_fd = 0;
	SET.cp = 0;
	shell->ccp = (t_ccp *)malloc(sizeof(t_ccp));
	shell->ccp->beg = 0;
	shell->ccp->str = NULL;
	shell->builtin[9] = "<<";
	shell->builtin[10] = NULL;
	ENABLE.paste = 0;
	initcolor(shell);
	init_shell(shell, environ);
	ft_hash(shell);
	terminit(shell);
	return (shell);
}
