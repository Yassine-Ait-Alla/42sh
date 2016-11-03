/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 16:48:21 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 05:04:52 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char			*insert(char *s, int c, char new)
{
	char				*ret;
	int					i;

	ret = (char *)malloc(sizeof(char) * ft_strlen(s) + 2);
	i = 0;
	while (i < c)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = new;
	while (s[i])
	{
		ret[i + 1] = s[i];
		i++;
	}
	ret[i + 1] = '\0';
	return (ret);
}

static char			*insert_del(t_shell *shell, char *s)
{
	int					i;
	int					y;
	char				*ret;

	ret = (char *)malloc(sizeof(char) * SET.cmdlen);
	i = 0;
	y = SET.cursor;
	while (i < y - 1)
	{
		ret[i] = s[i];
		i++;
	}
	while (s[y])
	{
		ret[i] = s[y];
		y++;
		i++;
	}
	ret[i] = '\0';
	SET.cursor--;
	SET.cmdlen--;
	SET.pos = SET.pos > 1 ? SET.pos - 1 : COL;
	SET.line = SET.pos == COL ? SET.line - 1 : SET.line;
	return (ret);
}

char				*backspacer(t_shell *shell, char *s)
{
	int					i;
	char				*ret;

	if (SET.cursor < SET.cmdlen && SET.cursor)
		return (insert_del(shell, s));
	else if (SET.cmdlen)
	{
		ret = (char *)malloc(sizeof(char) * SET.cmdlen);
		i = 0;
		while (i < SET.cmdlen - 1)
		{
			ret[i] = s[i];
			i++;
		}
		ret[i] = '\0';
		SET.cursor--;
		SET.cmdlen--;
		SET.pos = SET.pos > 1 ? SET.pos - 1 : COL;
		SET.line = SET.pos == COL ? SET.line - 1 : SET.line;
		return (ret);
	}
	return (NULL);
}

char				*reg_prompt(t_shell *shell, char *str, int j)
{
	int					i;

	if (j)
		puterm("ei");
	i = SET.cursor;
	clear_line(shell);
	prompter(shell);
	display(shell, str);
	i = SET.cmdlen;
	while (i-- > SET.cursor)
		puterm("le");
	if (j)
		puterm("im");
	return (str);
}

char				*regulate(char *save, char buf[4], t_shell *shell)
{
	SET.cmd = ft_strdup(save);
	if (BUF == 4 || BUF == 127 || SELECT || SEL_CHECK || PASTE_OK)
		return (regulator(shell, buf, save));
	if (ENABLE.hist == 1 && HST->ok == 0)
	{
		HST->save = ft_strdup(save);
		HST->ok = 1;
	}
	if (K_RIGHT || K_LEFT || C || K_HOME || K_END)
		return (reg_prompt(shell, SET.cmd, ENABLE.insert));
	if (REGULAR && !SPECIAL && ft_isprint(BUF))
	{
		if (ENABLE.insert == 1)
			return (reg_prompt(shell, insert(save, SET.cursor - 1, buf[0]), 1));
		return (reg_prompt(shell, ft_strjoin(save, buf), 0));
	}
	if (ENABLE.hist == 1)
		return (reg_prompt(shell, HST->hist[HST->index], ENABLE.insert));
	else if (ENABLE.hist == 0 && HST->ok == 1 && K_DOWN)
		return (reg_prompt(shell, HST->save, ENABLE.insert));
	return (reg_prompt(shell, SET.cmd, ENABLE.insert));
}
