/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 16:09:39 by yaitalla          #+#    #+#             */
/*   Updated: 2016/06/30 05:39:26 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

typedef enum		e_reetype
{
	B_SEMICOL,
	B_AND,
	B_OR,
	B_PIPE,
	B_CMD
}					t_reetype;

typedef enum		e_way
{
	W_NONE,
	LEFT,
	RIGHT
}					t_way;

typedef struct		s_ree
{
	struct s_cmd	*cmd;
	struct s_ree	*parent;
	struct s_ree	*left;
	struct s_ree	*right;
	t_reetype		type;
	int				fd;
	int				*pfd;
}					t_ree;

typedef enum		e_iotype
{
	IO_DEF,
	IO_PIPE,
	IO_TRUNC,
	IO_APPEND,
	IO_OUT,
	IO_READ
}					t_iotype;

typedef struct		s_io
{
	int				fd;
	char			*file;
	t_ree			*node;
	t_iotype		type;
}					t_io;

typedef struct		s_cmd
{
	char			*path;
	char			**arg;
	t_io			fdin;
	t_io			fdout;
}					t_cmd;

#endif
