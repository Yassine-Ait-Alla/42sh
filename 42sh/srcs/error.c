/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 16:32:41 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:02:42 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void	error(char *err)
{
	if (ft_strcmp(err, "MALLOC") == 0)
		ft_putendl("Malloc error.");
	if (ft_strcmp(err, "OPENDIR") == 0)
		ft_putendl("Opendir() error.");
	if (ft_strcmp(err, "CLOSEDIR") == 0)
		ft_putendl("Closedir() error.");
	return ;
}

void	term_error(char *err)
{
	if (!ft_strcmp(err, "GETENV"))
		ft_putstr("getenv() error\n");
	if (!ft_strcmp(err, "TGETENT"))
		ft_putstr("tgetent() error\n");
	if (!ft_strcmp(err, "TCGETATTR"))
		ft_putstr("tcgetattr() error\n");
	if (!ft_strcmp(err, "TCSETATTR"))
		ft_putstr("TCSETATTR() error\n");
}
