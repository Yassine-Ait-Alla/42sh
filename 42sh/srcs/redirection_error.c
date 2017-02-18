/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:55:45 by lubaujar          #+#    #+#             */
/*   Updated: 2016/05/03 15:55:49 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void	redirection_error(char *file)
{
	ft_putstr("42sh: no such file or directory: ");
	ft_putstr(file);
	ft_putchar('\n');
}

int		redirection_error_2(void)
{
	ft_putstr("42sh: Missing name for redirect.\n");
	return (0);
}

void	redirection_error_3(int err)
{
	if (err == 1)
		ft_putstr("42sh: Ambiguous output redirect.\n");
	else if (err == 2)
		ft_putstr("42sh: Ambiguous input redirect.\n");
	return ;
}

int		redirection_error_4(void)
{
	ft_putstr("42sh: Invalid null command.\n");
	return (0);
}
