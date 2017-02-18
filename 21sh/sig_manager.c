/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 17:30:52 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 04:15:42 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		continuer(void)
{
	t_shell		*shell;

	shell = NULL;
	shell = reset(1, shell);
	shell->trial.term.c_lflag &= ~(ICANON | ECHO);
	shell->trial.term.c_cc[VMIN] = 1;
	shell->trial.term.c_cc[VTIME] = 0;
	tcsetattr(0, 0, &(shell->trial.term));
	signal(SIGTSTP, sig_catcher);
}

void			sig_catcher(int i)
{
	if (i == SIGCONT)
		continuer();
	else if (i == SIGTSTP)
		continuer();
}

/*
**	else if (i == SIGWINCH)
**		resizer();
**	else
**		canceller();
*/

void			signaler(void)
{
	int			i;

	i = 1;
	while (i < 32)
	{
		signal(i, sig_catcher);
		i++;
	}
}
