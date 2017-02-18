/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 18:32:45 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 11:26:41 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void					free_tree(t_ree *tree)
{
	if (tree)
	{
		free_tree(tree->left);
		free_tree(tree->right);
		if (tree->cmd)
			free_cmd(tree->cmd);
		if (tree->pfd)
			free(tree->pfd);
		if (tree->fd != -1)
			close(tree->fd);
		free(tree);
	}
}

void					free_env(char ***env)
{
	int						i;

	i = 0;
	while ((*env)[i])
	{
		free((*env)[i]);
		i++;
	}
	if (*env != NULL)
		free(*env);
}

static void				free_hash(t_hash **h)
{
	t_hash					*temp;

	while (*h)
	{
		temp = *h;
		*h = temp->next;
		free(temp->name);
		free(temp->path);
		free(temp);
	}
}

static void				free_built(char **b)
{
	int						i;

	i = 0;
	while (i < ft_tablen(b))
	{
		free(b[i]);
		i++;
	}
}

void					ft_exit(t_shell **shell, char **arg)
{
	int						status;

	status = (*shell)->status;
	if (arg && ft_tablen(arg) >= 2)
		status = ft_atoi(arg[1]);
	if ((*shell)->setup.no_env)
		free_env(&((*shell)->env));
	free((*shell)->path);
	free((*shell)->pwd);
	free((*shell)->old_pwd);
	free((*shell)->cmd);
	free((*shell)->home);
	free_hash(&((*shell)->hash));
	free_built((*shell)->builtin);
	if ((*shell)->ast)
		free_tree((*shell)->ast);
	free(*shell);
	exit(status);
}
