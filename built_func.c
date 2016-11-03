/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 17:38:56 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/14 12:02:37 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void					initcolor(t_shell *shell)
{
	SET.color = ft_strdup(GREEN);
	init_name(shell);
	SET.color_list[0] = ft_strdup(DEFAULT);
	SET.color_list[1] = ft_strdup(RED);
	SET.color_list[2] = ft_strdup(BLUE);
	SET.color_list[3] = ft_strdup(CYAN);
	SET.color_list[4] = ft_strdup(BLACK);
	SET.color_list[5] = ft_strdup(GREEN);
	SET.color_list[6] = ft_strdup(BROWN);
	SET.color_list[7] = ft_strdup(MAGENTA);
	SET.color_list[8] = ft_strdup(BOLD_RED);
	SET.color_list[9] = ft_strdup(BOLD_BLUE);
	SET.color_list[10] = ft_strdup(BOLD_DEFAULT);
	SET.color_list[11] = ft_strdup(BOLD_CYAN);
	SET.color_list[12] = ft_strdup(LIGHT_GREY);
	SET.color_list[13] = ft_strdup(BOLD_BLACK);
	SET.color_list[14] = ft_strdup(BOLD_GREEN);
	SET.color_list[15] = ft_strdup(BOLD_BROWN);
	SET.color_list[16] = ft_strdup(BOLD_MAGENTA);
	SET.color_list[17] = ft_strdup(BOLD_LIGHT_GREY);
	SET.color_list[18] = NULL;
}

void					go_down(t_shell *shell)
{
	SET.pos = 1;
	while (SET.cursor < SET.cmdlen)
	{
		SET.cursor++;
		if ((SET.cursor + SET.prompt_len) > COL)
			SET.pos++;
	}
}

char					*regulator(t_shell *shell, char buf[4], char *save)
{
	if (PASTE_OK)
	{
		SET.cmd = ft_strdup(paste_str(shell));
		SET.test = 0;
		return (SET.cmd);
	}
	if (BUF == 4)
	{
		if (SET.cmdlen == 0)
			exit(0);
		if (SET.cursor < SET.cmdlen)
		{
			go_right(shell);
			return (reg_prompt(shell, backspacer(shell, save), 1));
		}
	}
	if (SET.cursor && BUF == 127)
		return (reg_prompt(shell, backspacer(shell, save), ENABLE.insert));
	if (SELECT || SEL_CHECK)
		selection(shell);
	if (REGULAR && !SPECIAL && !SELECT && BUF != 4)
		return (regulate(save, buf, shell));
	return (reg_prompt(shell, SET.cmd, ENABLE.insert));
}

t_shell					*reset(int i, t_shell *shell)
{
	static t_shell			*temp = NULL;

	if (!i)
		temp = shell;
	return (temp);
}

void					the_arrow(t_shell *shell, char buf[4])
{
	if (K_LEFT)
		go_left(shell);
	if (K_RIGHT)
		go_right(shell);
	if (SET.cp == 1)
		count(shell);
}
