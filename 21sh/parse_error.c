/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 16:09:25 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 10:29:33 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int			error_display(char *token)
{
	putcolor("Parse error near \'", DEFAULT, 2, 0);
	putcolor(token, BOLD_RED, 2, 0);
	putcolor("\'\n", DEFAULT, 2, 0);
	return (1);
}

int					parse_error(t_oken *tok)
{
	t_oken			*temp;

	temp = tok;
	while (temp)
	{
		if (PARS_ERR && temp->type != WORD && temp->type != SEMICOL)
			return (error_display(temp->tok));
		temp = temp->next;
	}
	return (0);
}
