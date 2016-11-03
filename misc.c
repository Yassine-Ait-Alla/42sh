/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 11:05:02 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 14:55:26 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int			here_prompt(t_shell *shell, int i, char **arg)
{
	char				*line;

	shell->heredoc = 1;
	line = NULL;
	shell->document = ft_strnew(1024);
	while (shell->heredoc)
	{
		ft_putstr("here document>");
		if (get_cmd(shell, 0, &line) == 0)
			return (1);
		if (recurcmp(line, shell->EOM) == 0)
			shell->heredoc = 0;
		else
		{
			ft_strcat(shell->document, line);
			ft_strcat(shell->document, "\n");
		}
	}
	TOKEN = create_token(split_doc(arg, i, shell->document), shell);
	if (TOKEN)
	{
		B_TREE = plant(TOKEN, NULL, W_NONE);
		STATUS = process(B_TREE, shell, 1);
	}
	return (STATUS);
}

int					heredoc(t_shell *shell, char **arg)
{
	int					i;

	i = 0;
	if (ft_strlen(arg[0]) == 2 && ft_tablen(arg) > 1)
	{
		shell->EOM = ft_strdup(arg[1]);
		i = 2;
	}
	else if (ft_strlen(arg[0]) > 2)
	{
		shell->EOM = ft_strdup(&(arg[0][2]));
		i = 1;
	}
	if (ft_tablen(arg) < 2)
		return (1);
	else
		return (here_prompt(shell, i, arg));
}

int					change_prompt(t_shell *shell)
{
	if (SET.prompt < 2)
		SET.prompt++;
	else
		SET.prompt = 0;
	return (0);
}

static void			prompter_3(t_shell *shell)
{
	putcolor(" ~~ 21sh ~~$> ", SET.color, 1, 0);
	SET.prompt_len = 14;
	SET.pos = shell->cmd == NULL ? SET.pos : 15;
}

void				prompter(t_shell *shell)
{
	if (shell->heredoc == 1)
	{
		ft_putstr("here document>");
		SET.prompt_len = 14;
		SET.pos = shell->cmd == NULL ? SET.pos : 15;
		return ;
	}
	if (SET.prompt == 0)
		prompter_1(shell);
	if (SET.prompt == 1)
		prompter_2(shell);
	if (SET.prompt == 2)
		prompter_3(shell);
}
