/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 08:34:25 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/12 02:04:44 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				display_historic(t_shell *shell, char **arg)
{
	int				i;

	i = 0;
	if (ft_tablen(arg) > 1)
	{
		syntax_hist(shell, arg);
		return (STATUS);
	}
	while (i < HST->len)
	{
		ft_putstr("    #");
		ft_putnbr(i + 1);
		ft_putstr(" : ");
		ft_putendl(HST->hist[i]);
		i++;
	}
	return (0);
}

static void		check_line(t_shell *shell, int len)
{
	len += SET.prompt_len;
	SET.max = 1;
	SET.line = 1;
	if (len >= COL)
	{
		while (len >= COL)
		{
			SET.max++;
			SET.line++;
			len -= COL;
		}
	}
}

static int		histup(t_shell *shell)
{
	if (HST->index > 0)
	{
		ENABLE.hist = 1;
		HST->index--;
		clear_line(shell);
		SET.cursor = ft_strlen(CMD);
		SET.cmdlen = SET.cursor;
		prompter(shell);
		ft_putstr(CMD);
		check_line(shell, SET.cmdlen);
	}
	return (SET.cmdlen + SET.prompt_len + 1);
}

static int		histdown(t_shell *shell)
{
	if (HST->index < HST->len - 1)
	{
		clear_line(shell);
		HST->index++;
		SET.cursor = ft_strlen(CMD);
		SET.cmdlen = SET.cursor;
		prompter(shell);
		ft_putstr(CMD);
		check_line(shell, SET.cmdlen);
		return (SET.prompt_len + SET.cmdlen + 1);
	}
	else if (HST->index == (HST->len - 1))
	{
		clear_line(shell);
		HST->index++;
		SET.cursor = ft_strlen(HST->save);
		SET.cmdlen = SET.cursor;
		prompter(shell);
		ft_putstr(HST->save);
		ENABLE.hist = 0;
		check_line(shell, SET.cmdlen);
		return (SET.prompt_len + SET.cmdlen + 1);
	}
	return (SET.pos);
}

void			historic(char buf[3], t_shell *shell)
{
	if (K_UP)
		SET.pos = histup(shell);
	if (K_DOWN)
		SET.pos = histdown(shell);
	while (SET.pos > COL)
		SET.pos -= COL;
}
