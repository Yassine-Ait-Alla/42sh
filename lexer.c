/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 14:40:35 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 10:12:02 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void					new_token(t_oken_type type, t_oken **tok, char *t)
{
	t_oken					*new;
	t_oken					*temp;

	new = (t_oken *)malloc(sizeof(t_oken));
	new->tok = t;
	new->type = type;
	if (*tok == NULL)
	{
		*tok = new;
		new->prev = NULL;
	}
	else
	{
		temp = *tok;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
	new->next = NULL;
}

static int				no_redir(t_oken **tok, char *cmd, int i)
{
	int						ret;

	ret = 0;
	while (P && !SPCHECK && !ft_isspace(P))
		ret++;
	if (ret > 0)
		new_token(WORD, tok, ft_strsub(cmd, i, ret));
	return (ret);
}

static int				redir(t_oken **tok, char *cmd, int i, t_shell *shell)
{
	if ((S == '1' || S == '2') && cmd[i + 1] == '>' && cmd[i + 2] == '&'
			&& cmd[i + 3] == '-')
		SET.close_fd = 1;
	if ((S == '>') && cmd[i + 1] == '&' && cmd[i + 2] == '-')
		SET.close_fd = 1;
	if (cmd[i + 1] == cmd[i] && S != '<')
		return (check_double(tok, cmd, i));
	else
		return (check_simple(tok, cmd, i));
}

t_oken					*create_token(char *cmd, t_shell *shell)
{
	t_oken					*tok;
	int						i;

	tok = NULL;
	i = 0;
	while (cmd[i])
	{
		while (ft_isspace(cmd[i]))
			i++;
		i += (S_CHECK_FD) ? redir(&tok, cmd, i, shell) : no_redir(&tok, cmd, i);
	}
	if (parse_error(tok))
	{
		token_destroyer(&tok);
		return (NULL);
	}
	return (tok);
}
