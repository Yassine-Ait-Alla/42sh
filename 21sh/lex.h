/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 16:13:12 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 09:55:30 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

typedef enum		e_oken_type
{
	SEMICOL,
	PIPE,
	REDIR_RR,
	REDIR_R,
	REDIR_L,
	AND,
	OR,
	WORD,
}					t_oken_type;

typedef struct		s_oken
{
	char			*tok;
	t_oken_type		type;
	struct s_oken	*prev;
	struct s_oken	*next;
}					t_oken;

int					parse_error(t_oken *tok);
int					check_simple(t_oken **tok, char *cmd, int i);
int					check_double(t_oken **tok, char *cmd, int i);
t_oken				*check_condition(t_oken *token);
t_oken				*brancher(t_oken *tok);
t_oken				*special_token(t_oken *token);
t_oken				*check_token(t_oken_type type, t_oken *token);
void				new_token(t_oken_type type, t_oken **tok, char *t);
void				token_destroyer(t_oken **token);
void				token_eraser(t_oken **token, t_oken *tok);

#endif
