/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 15:54:39 by yaitalla          #+#    #+#             */
/*   Updated: 2016/06/30 05:42:30 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			command_pipe(t_ree *node)
{
	t_ree				*temp;

	if (node->parent && node->parent->type == B_PIPE)
	{
		if (node->parent->left == node)
		{
			node->cmd->fdout.type = IO_PIPE;
			node->cmd->fdout.node = node->parent;
		}
		if (node->parent->right == node)
		{
			node->cmd->fdin.type = IO_PIPE;
			node->cmd->fdin.node = node->parent;
			temp = node->parent;
			while (PAPA && PAPA->type == B_PIPE && PAPA->right == temp)
				temp = PAPA;
			if (PAPA && PAPA->type == B_PIPE && PAPA->left == temp)
			{
				node->cmd->fdout.type = IO_PIPE;
				node->cmd->fdout.node = PAPA;
			}
		}
	}
}

static void			command_in(t_ree *node, t_oken **token)
{
	t_cmd				*cmd;
	t_oken				*red;

	cmd = node->cmd;
	red = special_token(*token);
	if (red)
	{
		if (red->type == REDIR_L)
			cmd->fdin.type = IO_READ;
		cmd->fdin.file = ft_strdup(red->next->tok);
		token_eraser(token, red->next);
		token_eraser(token, red);
	}
}

static void			command_out(t_ree *node, t_oken **token)
{
	t_cmd				*cmd;
	t_oken				*red;

	cmd = node->cmd;
	red = special_token(*token);
	if (red && (red->type == REDIR_R || red->type == REDIR_RR))
	{
		OUT = red->type == REDIR_R ? IO_TRUNC : IO_APPEND;
		COMMAND = ft_strdup(red->next->tok);
		token_eraser(token, red->next);
		token_eraser(token, red);
	}
}

t_ree				*command_seed(t_ree *papa, t_way way, t_oken *token)
{
	t_ree				*ret;

	ret = command_node(papa, way);
	command_pipe(ret);
	command_out(ret, &token);
	command_in(ret, &token);
	command_arg(ret, &token);
	token_destroyer(&token);
	return (ret);
}

t_ree				*node_seed(t_ree *papa, t_way w, t_reetype type)
{
	t_ree				*ret;

	ret = (t_ree *)malloc(sizeof(t_ree));
	ret->cmd = NULL;
	ret->left = NULL;
	ret->right = NULL;
	ret->pfd = NULL;
	ret->type = type;
	ret->parent = papa;
	ret->fd = -1;
	if (w == LEFT)
		ret->parent->left = ret;
	if (w == RIGHT)
		ret->parent->right = ret;
	return (ret);
}
