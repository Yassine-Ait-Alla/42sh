/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 15:55:25 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 14:25:12 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char			*check_path(char *arg, t_hash *hash)
{
	if (access(arg, F_OK) == 0)
	{
		while (hash)
		{
			if (recurcmp(hash->path, arg) == 0)
				hash->time++;
			hash = hash->next;
		}
		return (ft_strdup(arg));
	}
	else
	{
		while (hash)
		{
			if (recurcmp(hash->name, arg) == 0)
			{
				hash->time++;
				return (ft_strdup(hash->path));
			}
			hash = hash->next;
		}
		return (NULL);
	}
}

static int			check_in(t_io fdin)
{
	int					fd;

	fd = -1;
	if (fdin.type == IO_DEF)
		return (STDIN_FILENO);
	if (fdin.type == IO_PIPE)
		return (fdin.node->pfd[0]);
	if (fdin.type == IO_READ)
		fd = open(fdin.file, O_RDONLY);
	return (fd);
}

static int			check_out(t_io fdout, int close_fd)
{
	int					fd;

	fd = -1;
	if (close_fd)
	{
		putcolor("CLOSE", BOLD_RED, 1, 1);
		return (open("/dev/null", O_CREAT | O_WRONLY | O_TRUNC, 0644));
	}
	if (fdout.type == IO_DEF)
		return (STDOUT_FILENO);
	if (fdout.type == IO_PIPE)
		return (fdout.node->pfd[1]);
	if (fdout.type == IO_TRUNC)
	{
		if (close_fd == 0)
			fd = open(fdout.file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else
			fd = open("/dev/null", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	if (fdout.type == IO_APPEND)
		fd = open(fdout.file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fdout.type == IO_OUT)
		fd = fdout.fd;
	return (fd);
}

int					path_cmd(t_ree *tree, t_shell *shell, int i, int fdout)
{
	int					fdin;
	pid_t				pid;

	pid = 0;
	fdin = check_in(tree->cmd->fdin);
	tree->cmd->path = check_path(tree->cmd->arg[0], shell->hash);
	if (tree->cmd->path)
	{
		if (i)
			pid = fork();
		if (pid == 0)
			cmd_son(tree->cmd, shell, fdin, fdout);
		if (pid > 0)
			wait(&STATUS);
	}
	else
	{
		putcolor("21_SH: command not found: ", DEFAULT, 2, 0);
		putcolor(tree->cmd->arg[0], DEFAULT, 2, 1);
		STATUS = 127;
		if (!i)
			ft_exit(&shell, NULL);
	}
	return (STATUS);
}

int					cmd_proc(t_ree *tree, t_shell *shell, int i)
{
	int					fd;

	fd = check_out(tree->cmd->fdout, SET.close_fd);
	if (is_built(tree->cmd->arg[0], shell))
		return (built(tree->cmd->arg, shell, fd, i));
	else
		return (path_cmd(tree, shell, i, fd));
	return (127);
}
