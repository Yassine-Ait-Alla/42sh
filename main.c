/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 12:35:51 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 05:10:16 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			execute(t_shell *shell)
{
	while (1)
		prompt(shell);
}

static void			launcher(void)
{
	putcolor("                           ::::::::        ", BOLD_CYAN, 1, 0);
	putcolor("::::                  ", BOLD_CYAN, 1, 1);
	putcolor("                         :+:    :+:      ::", BOLD_CYAN, 1, 0);
	putcolor("+::                   ", BOLD_CYAN, 1, 1);
	putcolor("                              +:+      +:  ", BOLD_CYAN, 1, 0);
	putcolor("+:+    SSSSS  H     H", BOLD_CYAN, 1, 1);
	putcolor("                           +#+        #   +", BOLD_CYAN, 1, 0);
	putcolor(":+    S       H     H", BOLD_CYAN, 1, 1);
	putcolor("                        +#+              +#", BOLD_CYAN, 1, 0);
	putcolor("+     SSSSS   HHHHHHH", BOLD_CYAN, 1, 1);
	putcolor("                      #+#               #+#", BOLD_CYAN, 1, 0);
	putcolor("           S  H     H", BOLD_CYAN, 1, 1);
	putcolor("                    ###########       #####", BOLD_CYAN, 1, 0);
	putcolor("      SSSSS   H     H", BOLD_CYAN, 1, 1);
}

int					main(void)
{
	extern char			**environ;
	t_shell				*shell;

	signaler();
	shell = init_all(environ);
	reset(0, shell);
	if (COL > 66)
		launcher();
	execute(shell);
	termclose(shell);
	return (0);
}
