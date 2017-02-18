/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabplusone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <yaitalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/29 23:56:13 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/14 10:57:30 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "colors.h"

char		**tabtabplus(char **av, char *str)
{
	char		**tablo;
	int			i;
	int			j;
	int			k;

	k = 0;
	j = ft_tablen(av);
	i = 0;
	tablo = (char **)malloc(sizeof(char *) * j + 2);
	while (i < j)
	{
		tablo[i] = (char *)malloc(sizeof(char) * ft_strlen(av[i]) + 1);
		tablo[i] = ft_strdup(av[i]);
		i++;
	}
	tablo[i] = ft_strdup(str);
	i++;
	tablo[i] = "\0";
	return (tablo);
}
