/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 15:47:11 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 04:19:19 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void				upper(t_shell *shell)
{
	int						i;

	i = SET.cursor + SET.prompt_len;
	if (SET.line > 2)
	{
		TEST;
		SET.cursor -= (COL - 1);
	}
	else
	{
		if (SET.pos <= SET.prompt_len)
		{
			SET.cursor = 0;
			SET.pos = SET.prompt_len + 1;
		}
		else
			SET.cursor = (SET.cursor - COL) + 1;
	}
	while (i > SET.cursor)
	{
		puterm("le");
		i--;
	}
	SET.line--;
	ENABLE.insert = 1;
}

static void				downer(t_shell *shell)
{
	int						i;

	i = 1;
	puterm("do");
	if (SET.line <= (SET.max - 2))
	{
		while (i++ < (SET.pos - 1))
			puterm("nd");
		SET.cursor += COL - 1;
	}
	else if (SET.cmdlen < COL)
		go_down(shell);
	else
	{
		while (i++ < (SET.pos - 1) && SET.cursor < SET.cmdlen)
			puterm("nd");
		if (SET.cursor == SET.cmdlen)
			SET.pos = i;
		SET.cursor += COL - 1;
	}
	SET.line++;
}

void					key_checker(t_shell *shell, char buf[4])
{
	move_cursor(buf, shell);
	if (buf[0] == 12)
	{
		puterm("cl");
		prompter(shell);
	}
	if (C_UP && SET.line > 1)
		upper(shell);
	if (C_DOWN && SET.max > SET.line)
		downer(shell);
	if (K_UP || (K_DOWN && ENABLE.hist == 1))
		historic(buf, shell);
	if (COPY && SET.cp == 1)
		copy_str(shell);
}

void					go_left(t_shell *shell)
{
	if (SET.cursor)
	{
		ENABLE.insert = 1;
		puterm("im");
		puterm("le");
		SET.cursor--;
		if (SET.pos > 1)
			SET.pos--;
		else
		{
			SET.pos = COL;
			SET.line--;
		}
	}
}

void					go_right(t_shell *shell)
{
	if (SET.cursor < SET.cmdlen)
	{
		if (SET.max > 1 && SET.pos == COL)
		{
			puterm("nd");
			SET.pos = 1;
			SET.line++;
		}
		else
		{
			puterm("nd");
			SET.pos = SET.pos == COL ? 1 : SET.pos + 1;
		}
		SET.cursor++;
	}
}
