/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 02:25:12 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 14:54:46 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int					check_double(t_oken **tok, char *cmd, int i)
{
	if (cmd[i] == '>')
		new_token(REDIR_RR, tok, ft_strsub(cmd, i, 2));
	if (cmd[i] == '|')
		new_token(OR, tok, ft_strsub(cmd, i, 2));
	if (cmd[i] == '&')
		new_token(AND, tok, ft_strsub(cmd, i, 2));
	return (2);
}

int					check_simple(t_oken **tok, char *cmd, int i)
{
	if (cmd[i] == ';')
		new_token(SEMICOL, tok, ft_strsub(cmd, i, 1));
	if (cmd[i] == '>')
		new_token(REDIR_R, tok, ft_strsub(cmd, i, 1));
	if (cmd[i] == '|')
		new_token(PIPE, tok, ft_strsub(cmd, i, 1));
	if (cmd[i] == '<')
		new_token(REDIR_L, tok, ft_strsub(cmd, i, 1));
	return (1);
}
