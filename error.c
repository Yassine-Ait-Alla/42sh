/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 17:31:21 by yaitalla          #+#    #+#             */
/*   Updated: 2016/04/27 17:33:40 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int					cd_error(char *path, char *arg)
{
	DIR					*d;

	if ((d = opendir(path)) == NULL)
	{
		putcolor(arg, BOLD_DEFAULT, 2, 1);
		putcolor(": ", BOLD_DEFAULT, 2, 1);
		if (errno == ENOTDIR)
			putcolor("not a directory", MAGENTA, 2, 1);
		else if (errno == EACCES)
			putcolor("permission denied", MAGENTA, 2, 1);
		return (1);
	}
	if (d)
		closedir(d);
	return (0);
}
