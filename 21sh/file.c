/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 18:58:01 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 07:06:21 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void					liner(t_shell *shell)
{
	int						i;

	i = 0;
	if (SET.pos > COL)
	{
		SET.pos = 1;
		SET.line++;
		SET.max++;
	}
}

void					reset_command(t_shell *shell)
{
	ENABLE.hist = 0;
	if (recurcmp(shell->cmd, "") != 0)
	{
		HST->len++;
		HST->index = HST->len;
		HST->hist[HST->len - 1] = ft_strdup(shell->cmd);
	}
	free(shell->cmd);
	shell->cmd = NULL;
	HST->ok = 0;
	SET.pos = SET.prompt_len + 1;
	SET.cmdlen = 0;
	SET.close_fd = 0;
	SET.cursor = 0;
	SET.test = 0;
	SET.max = 1;
	SET.line = 1;
	ENABLE.insert = 0;
	puterm("ei");
}

void					cmd_son(t_cmd *c, t_shell *shell, int fdin, int fdout)
{
	if (fdin != STDIN_FILENO)
		dup2(fdin, STDIN_FILENO);
	if (fdout != STDOUT_FILENO)
		dup2(fdout, STDOUT_FILENO);
	execve(c->path, c->arg, shell->env);
	exit(EXIT_FAILURE);
}

void					token_destroyer(t_oken **token)
{
	t_oken					*temp;

	while (*token)
	{
		temp = *token;
		*token = temp->next;
		free(temp->tok);
		free(temp);
	}
}

void					free_cmd(t_cmd *c)
{
	int						i;

	i = 0;
	while (c->arg[i])
		free(c->arg[i++]);
	free(c->arg);
	free(c->path);
	if (c->fdin.file)
		free(c->fdin.file);
	if (c->fdout.file)
		free(c->fdout.file);
	free(c);
}
