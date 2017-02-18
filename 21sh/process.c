/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 16:34:18 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/12 01:16:57 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int			piper(t_ree *tree, t_shell *shell, int c)
{
	pid_t				pid;
	int					i;

	pid = 0;
	i = 0;
	if (c)
		pid = fork();
	if (pid == 0)
		pipe_son(tree, shell, &i);
	else
		wait(&i);
	return (i);
}

static int			or_if(t_ree *tree, t_shell *shell)
{
	int					i;

	i = process(tree->left, shell, 1);
	if (i != 0)
		i = process(tree->right, shell, 1);
	return (i);
}

static int			and_if(t_ree *tree, t_shell *shell)
{
	int					i;

	i = process(tree->left, shell, 1);
	if (i == 0)
		i = process(tree->right, shell, 1);
	return (i);
}

static int			semicol(t_ree *tree, t_shell *shell)
{
	int					i;

	if (tree->left)
		i = process(tree->left, shell, 1);
	if (tree->right)
		i = process(tree->right, shell, 1);
	return (i);
}

int					process(t_ree *tree, t_shell *shell, int c)
{
	if (TYPE == B_SEMICOL)
		STATUS = semicol(tree, shell);
	if (TYPE == B_AND)
		STATUS = and_if(tree, shell);
	if (TYPE == B_OR)
		STATUS = or_if(tree, shell);
	if (TYPE == B_PIPE)
		STATUS = piper(tree, shell, c);
	if (TYPE == B_CMD)
		STATUS = cmd_proc(tree, shell, c);
	return (STATUS);
}
