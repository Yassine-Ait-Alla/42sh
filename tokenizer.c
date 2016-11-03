/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 16:03:47 by yaitalla          #+#    #+#             */
/*   Updated: 2016/04/17 19:01:45 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				token_eraser(t_oken **token, t_oken *tok)
{
	if (*token == tok)
		*token = tok->next;
	if (tok->prev)
		tok->prev->next = tok->next;
	if (tok->next)
		tok->next->prev = tok->prev;
	free(tok->tok);
	free(tok);
}

t_oken				*special_token(t_oken *token)
{
	t_oken				*temp;

	temp = token;
	while (temp)
	{
		if (temp->type != WORD)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

t_oken				*check_condition(t_oken *token)
{
	t_oken				*ret;
	t_oken				*temp;

	temp = token;
	ret = NULL;
	while (temp)
	{
		if (temp->type == OR || temp->type == AND)
			ret = temp;
		temp = temp->next;
	}
	return (ret);
}

t_oken				*brancher(t_oken *tok)
{
	t_oken				*token_right;

	token_right = tok->next;
	if (tok->prev)
		tok->prev->next = NULL;
	if (tok->next)
		tok->next->prev = NULL;
	free(tok->tok);
	free(tok);
	return (token_right);
}
