/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 18:15:38 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 11:02:52 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int					ft_env(t_shell *shell, int fdout)
{
	int					i;
	int					j;

	i = 0;
	j = ft_tablen(shell->env);
	while (i < j)
	{
		putcolor(ENV, DEFAULT, fdout, 1);
		i++;
	}
	return (0);
}

int					is_built(char *arg, t_shell *shell)
{
	int					i;

	i = 0;
	while (shell->builtin[i])
	{
		if (recurcmp(arg, shell->builtin[i]) == 0
				|| ft_strncmp(arg, "<<", 2) == 0)
			return (1);
		i++;
	}
	return (0);
}

void				prompter_1(t_shell *shell)
{
	if (SET.cursor < 100)
	{
		putcolor("0", SET.color, 1, 0);
		if (SET.cursor < 10)
			putcolor("0", SET.color, 1, 0);
	}
	putcolor(ft_itoa(SET.cursor), SET.color, 1, 0);
	putcolor(" ", SET.color, 1, 0);
	if (SET.pos < 100)
	{
		putcolor("0", SET.color, 1, 0);
		if (SET.pos < 10)
			putcolor("0", SET.color, 1, 0);
	}
	putcolor(ft_itoa(SET.pos), SET.color, 1, 0);
	putcolor(" ", SET.color, 1, 0);
	putcolor(ft_itoa(ENABLE.paste), SET.color, 1, 0);
	putcolor(ft_itoa(SET.cp), SET.color, 1, 0);
	putcolor(" $> ", SET.color, 1, 0);
	SET.prompt_len = 14;
	SET.pos = shell->cmd == NULL ? SET.pos : SET.prompt_len + 1;
}

static void			pipe_proc(t_ree *right)
{
	t_cmd				*temp;

	temp = right->cmd;
	if (temp->fdout.type == IO_TRUNC)
	{
		temp->fdout.fd = open(temp->fdout.file, O_CREAT | O_WRONLY | O_TRUNC,
				0664);
		temp->fdout.type = IO_OUT;
	}
	if (temp->fdout.type == IO_APPEND)
	{
		temp->fdout.fd = open(temp->fdout.file, O_CREAT | O_WRONLY | O_APPEND,
				0664);
		temp->fdout.type = IO_OUT;
	}
}

void				pipe_son(t_ree *tree, t_shell *shell, int *i)
{
	pid_t				pid;
	int					*pfd;

	pipe_proc(tree->right);
	pfd = (int *)malloc(sizeof(int) * 2);
	pipe(pfd);
	tree->pfd = pfd;
	pid = fork();
	if (pid == 0)
	{
		close(pfd[0]);
		process(tree->left, shell, 0);
	}
	else
	{
		close(pfd[1]);
		wait(i);
		cmd_proc(tree->right, shell, 0);
	}
}
