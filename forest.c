/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 14:23:14 by yaitalla          #+#    #+#             */
/*   Updated: 2016/04/21 19:41:31 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_ree			*semicol_tree(t_ree *papa, t_way w, t_oken *t_left, t_oken *tok)
{
	t_ree			*node;
	t_oken			*right;
	int				i;

	i = 0;
	if (tok == t_left)
		i = 1;
	node = node_seed(papa, w, B_SEMICOL);
	right = brancher(tok);
	if (!i)
		node->left = plant(t_left, node, LEFT);
	else
		node->left = NULL;
	node->right = plant(right, node, RIGHT);
	return (node);
}

t_ree			*pipe_tree(t_ree *papa, t_way w, t_oken *t_left, t_oken *tok)
{
	t_ree			*node;
	t_oken			*right;

	node = node_seed(papa, w, B_PIPE);
	right = brancher(tok);
	node->left = plant(t_left, node, LEFT);
	node->right = plant(right, node, RIGHT);
	return (node);
}

t_ree			*or_tree(t_ree *papa, t_way w, t_oken *t_left, t_oken *tok)
{
	t_ree			*node;
	t_oken			*right;

	node = node_seed(papa, w, B_OR);
	right = brancher(tok);
	node->left = plant(t_left, node, LEFT);
	node->right = plant(right, node, RIGHT);
	return (node);
}

t_ree			*and_tree(t_ree *papa, t_way w, t_oken *t_left, t_oken *tok)
{
	t_ree			*node;
	t_oken			*right;

	node = node_seed(papa, w, B_AND);
	right = brancher(tok);
	node->left = plant(t_left, node, LEFT);
	node->right = plant(right, node, RIGHT);
	return (node);
}

t_ree			*plant(t_oken *token, t_ree *papa, t_way w)
{
	t_oken			*tok;

	if (token == NULL)
		return (NULL);
	tok = check_token(SEMICOL, token);
	if (tok)
		return (semicol_tree(papa, w, token, tok));
	tok = check_condition(token);
	if (tok && tok->type == OR)
		return (or_tree(papa, w, token, tok));
	if (tok && tok->type == AND)
		return (and_tree(papa, w, token, tok));
	tok = check_token(PIPE, token);
	if (tok)
		return (pipe_tree(papa, w, token, tok));
	return (command_seed(papa, w, token));
}
