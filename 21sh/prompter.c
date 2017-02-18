/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 00:22:02 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 07:15:49 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				init_name(t_shell *shell)
{
	SET.color_name[0] = ft_strdup("default");
	SET.color_name[1] = ft_strdup("red");
	SET.color_name[2] = ft_strdup("blue");
	SET.color_name[3] = ft_strdup("cyan");
	SET.color_name[4] = ft_strdup("black");
	SET.color_name[5] = ft_strdup("green");
	SET.color_name[6] = ft_strdup("brown");
	SET.color_name[7] = ft_strdup("magenta");
	SET.color_name[8] = ft_strdup("bold_red");
	SET.color_name[9] = ft_strdup("bold_blue");
	SET.color_name[10] = ft_strdup("bold_default");
	SET.color_name[11] = ft_strdup("bold_cyan");
	SET.color_name[12] = ft_strdup("light_grey");
	SET.color_name[13] = ft_strdup("bold_black");
	SET.color_name[14] = ft_strdup("bold_green");
	SET.color_name[15] = ft_strdup("bold_brown");
	SET.color_name[16] = ft_strdup("bold_magenta");
	SET.color_name[17] = ft_strdup("bold_light_grey");
	SET.color_name[18] = NULL;
}

void				prompter_2(t_shell *shell)
{
	int					i;

	i = ft_tablen(HST->hist);
	if (STATUS < 100)
	{
		putcolor("0", SET.color, 1, 0);
		if (STATUS < 10)
			putcolor("0", SET.color, 1, 0);
	}
	putcolor(ft_itoa(STATUS), SET.color, 1, 0);
	putcolor(" ", SET.color, 1, 0);
	if (SET.cursor < 100)
	{
		putcolor("0", SET.color, 1, 0);
		if (SET.cursor < 10)
			putcolor("0", SET.color, 1, 0);
	}
	putcolor(ft_itoa(SET.cursor), SET.color, 1, 0);
	putcolor(" ", SET.color, 1, 0);
	if (i < 10)
		putcolor("0", SET.color, 1, 0);
	putcolor(ft_itoa(i), SET.color, 1, 0);
	putcolor(" $> ", DEFAULT, 1, 0);
	SET.prompt_len = 14;
	SET.pos = shell->cmd == NULL ? SET.pos : SET.prompt_len + 1;
}

int					change_color(t_shell *shell, char **arg)
{
	int					i;

	i = 0;
	while (i < 18 && (recurcmp(arg[1], SET.color_name[i]) != 0))
		i++;
	if (ft_tablen(arg) != 2 || i > 17)
	{
		putcolor("color: Error", BOLD_DEFAULT, 1, 1);
		putcolor("Usage: color [valid color name]", DEFAULT, 1, 1);
		return (1);
	}
	SET.color = ft_strdup(SET.color_list[i]);
	return (0);
}

static void			syn_error_history(t_shell *shell)
{
	putcolor("error history builtin", BOLD_DEFAULT, 1, 1);
	putcolor("usage: history [#history index]", DEFAULT, 1, 1);
	STATUS = 1;
}

void				syntax_hist(t_shell *shell, char **arg)
{
	int					i;

	if (ft_tablen(arg) > 2)
	{
		(syn_error_history(shell));
		return ;
	}
	i = ft_atoi(arg[1]);
	if (i < 1 || i > ft_tablen(HST->hist))
	{
		(syn_error_history(shell));
		return ;
	}
	TOKEN = create_token(HST->hist[i - 1], shell);
	if (TOKEN)
	{
		B_TREE = plant(TOKEN, NULL, W_NONE);
		STATUS = process(B_TREE, shell, 1);
	}
}
