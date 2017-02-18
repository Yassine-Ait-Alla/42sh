/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 01:30:20 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 05:06:50 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char				*paste_str(t_shell *shell)
{
	int					i;
	int					j;
	char				*ret;

	j = 0;
	i = 0;
	SET.cmdlen += ft_strlen(CCP->str);
	ret = (char *)malloc(sizeof(char) * SET.cmdlen + 1);
	while (j < SET.cmdlen)
	{
		if (j == SET.cursor)
		{
			while (CCP->str[SET.test])
			{
				ret[j] = CCP->str[SET.test];
				j++;
				SET.test++;
			}
		}
		ret[j] = SET.cmd[i];
		j++;
		i++;
	}
	ret[j] = '\0';
	return (normal(shell, ret, ENABLE.insert));
}

void				copy_str(t_shell *shell)
{
	int					i;
	int					j;

	i = 0;
	j = 0;
	while (j < SET.cmdlen)
	{
		if (SEL[j] == 1)
			i++;
		j++;
	}
	j = 0;
	while (SEL[j] == 0)
		j++;
	if (CCP->str != NULL)
		free(CCP->str);
	CCP->str = ft_strsub(SET.cmd, j, i);
	ENABLE.paste = 1;
	selection(shell);
}

void				display(t_shell *shell, char *str)
{
	int					i;

	i = 0;
	if (SET.cp == 0)
		ft_putstr(str);
	else
	{
		while (i < SET.cmdlen)
		{
			if (SEL[i] == 1)
			{
				puterm("so");
				ft_putchar(str[i]);
				puterm("se");
			}
			else
				ft_putchar(str[i]);
			i++;
		}
	}
}

void				selection(t_shell *shell)
{
	int					i;

	i = 0;
	if (SET.cp == 1)
	{
		free(SEL);
		SET.cp = 0;
		return ;
	}
	SET.cp = 1;
	shell->ccp->beg = SET.cursor;
	SEL = (int *)malloc(sizeof(int) * SET.cmdlen);
	while (i < SET.cmdlen)
	{
		SEL[i] = 0;
		i++;
	}
}

void				count(t_shell *shell)
{
	int					i;

	i = 0;
	if (shell->ccp->beg > SET.cursor)
	{
		while (i < SET.cmdlen)
		{
			SEL[i] = (i >= SET.cursor && i < shell->ccp->beg) ? 1 : 0;
			i++;
		}
	}
	if (shell->ccp->beg <= SET.cursor)
	{
		while (i < SET.cmdlen)
		{
			SEL[i] = (i <= SET.cursor && i >= shell->ccp->beg) ? 1 : 0;
			i++;
		}
	}
}
