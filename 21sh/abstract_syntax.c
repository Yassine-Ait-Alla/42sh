/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 19:39:21 by yaitalla          #+#    #+#             */
/*   Updated: 2016/06/30 05:41:37 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int			sizer(t_oken *token)
{
	t_oken				*temp;
	int					i;

	temp = token;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void				command_arg(t_ree *node, t_oken **token)
{
	t_cmd				*cmd;
	t_oken				*temp;
	char				**arg;
	int					i;
	int					size;

	cmd = node->cmd;
	temp = *token;
	size = sizer(temp);
	arg = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
	{
		arg[i++] = ft_strdup(temp->tok);
		temp = temp->next;
	}
	arg[i] = NULL;
	cmd->arg = arg;
}

static void			init_node(t_io *fd1, t_io *fd2)
{
	fd1->node = NULL;
	fd1->file = NULL;
	fd2->node = NULL;
	fd2->file = NULL;
}

t_ree				*command_node(t_ree *papa, t_way w)
{
	t_ree				*node;

	node = node_seed(papa, w, B_CMD);
	node->cmd = (t_cmd *)malloc(sizeof(t_cmd));
	node->cmd->path = NULL;
	node->cmd->arg = NULL;
	node->cmd->fdin.type = IO_DEF;
	node->cmd->fdout.type = IO_DEF;
	init_node(&node->cmd->fdin, &node->cmd->fdout);
	return (node);
}

t_oken				*check_token(t_oken_type type, t_oken *token)
{
	t_oken				*ret;
	t_oken				*temp;

	temp = token;
	ret = NULL;
	while (temp)
	{
		ret = temp->type == type ? temp : ret;
		temp = temp->next;
	}
	return (ret);
}
