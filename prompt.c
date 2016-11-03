/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 18:12:02 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 14:56:11 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int			check_save(char **save, char **line)
{
	char			*temp;

	if ((temp = ft_strchr(*save, '\n')))
	{
		*temp = '\0';
		*line = ft_strdup(*save);
		ft_strcpy(*save, temp + 1);
		return (1);
	}
	return (0);
}

static int			check_read(char *buf, char **save, char **line)
{
	char			*temp;

	if (!(*save))
		*save = "";
	if ((temp = ft_strchr(buf, '\n')))
	{
		*temp = '\0';
		*line = ft_strjoin(*save, buf);
		*save = ft_strdup(temp + 1);
		temp = NULL;
		return (1);
	}
	return (0);
}

static int			check_key(t_shell *shell, char buf[4])
{
	if (REGULAR && !SPECIAL && (ft_isprint(BUF) || BUF == 10))
	{
		if (BUF != 10 && BUF != 4 && !SELECT && (int)BUF > 0)
		{
			SET.cursor++;
			SET.pos++;
			SET.cmdlen++;
			liner(shell);
		}
		else if (ft_isprint(BUF) == 1 || BUF == 10)
			ft_putchar(BUF);
		return (1);
	}
	key_checker(shell, buf);
	return (0);
}

int					get_cmd(t_shell *shell, int const fd, char **line)
{
	static char		*save = NULL;
	char			*buf;
	int				r;

	if (save)
		if (check_save(&save, line))
			return (1);
	buf = ft_strnew(4);
	while ((r = read(fd, buf, 4)) > 0)
	{
		check_key(shell, buf);
		buf[r] = '\0';
		if (check_read(buf, &save, line))
			return (1);
		save = regulate(save, buf, shell);
	}
	if (r == -1)
		return (-1);
	if (save == NULL)
		return (0);
	*line = ft_strdup(save);
	ft_strdel(&save);
	return (1);
}

void				prompt(t_shell *shell)
{
	prompter(shell);
	if (get_cmd(shell, 0, &shell->cmd) == 0)
		exit(0);
	if (shell->cmd[0])
	{
		TOKEN = create_token(shell->cmd, shell);
		if (TOKEN)
		{
			B_TREE = plant(TOKEN, NULL, W_NONE);
			STATUS = process(B_TREE, shell, 1);
			free_tree(B_TREE);
			B_TREE = NULL;
		}
	}
	reset_command(shell);
}
