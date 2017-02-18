/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdocs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 11:54:15 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 14:50:01 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char				*split_doc(char **arg, int i, char *doc)
{
	char				*ret;
	int					j;

	j = i;
	ret = ft_strnew(1024);
	ft_strcat(ret, "echo ");
	ft_strcat(ret, doc);
	while (j < ft_tablen(arg))
	{
		ft_strcat(ret, arg[j]);
		j++;
	}
	return (ret);
}
