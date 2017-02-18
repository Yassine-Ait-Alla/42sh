/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <yaitalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/16 18:27:14 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 04:13:43 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			terminit(t_shell *shell)
{
	struct winsize	win;

	if (tgetent(NULL, "xterm-256color") < 1)
		return (0);
	if (tcgetattr(0, &(shell->trial.term)) == -1)
		return (0);
	shell->trial.term.c_lflag &= ~(ECHO | ICANON);
	shell->trial.term.c_cc[VMIN] = 1;
	shell->trial.term.c_cc[VTIME] = 0;
	ioctl(0, TIOCGWINSZ, &win);
	shell->trial.lins = win.ws_row;
	COL = win.ws_col + 1;
	if (tcsetattr(0, TCSADRAIN, &(shell->trial.term)) == -1)
		return (0);
	return (1);
}

int			termclose(t_shell *shell)
{
	shell->trial.term.c_lflag |= (ECHO | ICANON);
	if (tcsetattr(0, TCSADRAIN, &(shell->trial.term)) == -1)
		return (0);
	return (1);
}

int			tputchar(int c)
{
	write(2, &c, 1);
	return (0);
}

void		puterm(char *tc)
{
	tputs(tgetstr(tc, NULL), 1, tputchar);
}
