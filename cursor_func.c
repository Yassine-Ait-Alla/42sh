/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 21:31:42 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/09 04:50:41 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				clear_line(t_shell *shell)
{
	int					i;
	int					j;

	j = SET.line;
	i = SET.cursor;
	while (i++ < SET.cmdlen)
		puterm("nd");
	i += SET.prompt_len;
	while (j > 1 && SET.pos != 1)
	{
		puterm("dl");
		puterm("up");
		j--;
	}
	while (i--)
	{
		puterm("le");
	}
	while (i++ < (SET.prompt_len + SET.cmdlen))
	{
		puterm("dc");
	}
}
