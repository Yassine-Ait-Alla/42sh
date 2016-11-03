/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <yaitalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 15:52:05 by yaitalla          #+#    #+#             */
/*   Updated: 2015/08/23 02:23:47 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check_save(char **save, char **line)
{
	char	*temp;

	if ((temp = ft_strchr(*save, '\n')))
	{
		*temp = '\0';
		*line = ft_strdup(*save);
		ft_strcpy(*save, temp + 1);
		return (1);
	}
	return (0);
}

static int		check_read(char *buffer, char **save, char **line)
{
	char	*temp;

	if (!(*save))
		*save = "";
	if ((temp = ft_strchr(buffer, '\n')))
	{
		*temp = '\0';
		*line = ft_strjoin(*save, buffer);
		*save = ft_strdup(temp + 1);
		temp = NULL;
		return (1);
	}
	return (0);
}

int				get_next_line(int const fd, char **line)
{
	static char		*save = NULL;
	char			*buffer;
	int				r;

	if (save)
		if (check_save(&save, line))
			return (1);
	buffer = ft_strnew(BUFF_SIZE);
	while ((r = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[r] = '\0';
		if (check_read(buffer, &save, line))
			return (1);
		save = ft_strjoin(save, buffer);
	}
	if (r == -1)
		return (-1);
	if (save == NULL)
		return (0);
	*line = ft_strdup(save);
	ft_strdel(&save);
	return (1);
}
