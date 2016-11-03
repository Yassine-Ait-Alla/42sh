/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 16:54:10 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/06 21:39:10 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			left_word(t_shell *shell)
{
	puterm("im");
	ENABLE.insert = 1;
	if (SPACE)
	{
		while (SPACE)
		{
			puterm("le");
			SET.cursor--;
			SET.pos = SET.pos > 1 ? SET.pos - 1 : COL;
			SET.line = SET.pos == COL ? SET.line - 1 : SET.line;
		}
	}
	else
	{
		while (SET.cursor && !SPACE)
		{
			puterm("le");
			SET.cursor--;
			SET.pos = SET.pos > 1 ? SET.pos - 1 : COL;
			SET.line = SET.pos == COL ? SET.line - 1 : SET.line;
		}
	}
}

static void			right_word(t_shell *shell)
{
	if (SPACE)
	{
		while (SPACE && SET.cursor < SET.cmdlen)
		{
			puterm("nd");
			SET.cursor++;
			SET.pos = SET.pos > COL ? 1 : SET.pos + 1;
			SET.line = SET.pos == 1 ? SET.line + 1 : SET.line;
		}
	}
	else
	{
		while (SET.cursor < SET.cmdlen && !SPACE)
		{
			puterm("nd");
			SET.cursor++;
			SET.pos = SET.pos > COL ? 1 : SET.pos + 1;
			SET.line = SET.pos == 1 ? SET.line + 1 : SET.line;
		}
	}
}

static void			xcursor(char buf[4], t_shell *shell)
{
	if (SET.cursor && K_HOME)
	{
		if (ENABLE.insert == 0)
			ENABLE.insert = 1;
		while (SET.cursor)
		{
			puterm("le");
			SET.cursor--;
		}
		SET.pos = SET.prompt_len + 1;
		SET.line = 1;
	}
	if (K_END && SET.cursor < SET.cmdlen)
	{
		while (SET.cursor++ < SET.cmdlen)
		{
			puterm("nd");
			SET.pos = SET.pos > COL ? 1 : SET.pos + 1;
		}
		SET.cursor--;
		SET.line = SET.max;
		puterm("ei");
	}
}

static void			liner_del(t_shell *shell)
{
	int					i;

	i = ft_strlen(&(SET.cmd[SET.cursor]));
	puterm("le");
	puterm("ei");
	ft_putstr(&(SET.cmd[SET.cursor]));
	puterm("im");
	if (SET.line < SET.max)
	{
		puterm("do");
		puterm("ce");
		puterm("up");
	}
	puterm("ce");
	while (i--)
		puterm("le");
}

void				move_cursor(char buf[4], t_shell *shell)
{
	if (K_LEFT || K_RIGHT)
		the_arrow(shell, buf);
	if (C_RIGHT && SET.cursor < SET.cmdlen)
		right_word(shell);
	if (C_LEFT && SET.cursor)
		left_word(shell);
	if (K_HOME || K_END)
		xcursor(buf, shell);
	if (buf[0] == 127 && SET.cursor)
	{
		if (SET.line < SET.max)
			liner_del(shell);
		else
		{
			puterm("le");
			puterm("dc");
		}
	}
}
