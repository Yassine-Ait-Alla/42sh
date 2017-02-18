/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 18:07:52 by yaitalla          #+#    #+#             */
/*   Updated: 2016/04/21 16:03:39 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void				*create_hash(char *name, char *path)
{
	t_hash					*ret;
	char					*path_var;

	ret = (t_hash *)malloc(sizeof(t_hash));
	path_var = (char *)malloc(ft_strlen(name) + ft_strlen(path) + 2);
	ft_strcpy(path_var, path);
	ft_strcat(path_var, "/");
	ft_strcat(path_var, name);
	if (ret)
	{
		ret->name = ft_strdup(name);
		ret->path = path_var;
		ret->time = 0;
		ret->next = NULL;
	}
	return (ret);
}

void					recup(t_hash **hash_tab, char *name, char *path)
{
	t_hash					*new;
	t_hash					*temp;

	new = create_hash(name, path);
	if (*hash_tab == NULL)
		*hash_tab = new;
	else
	{
		temp = *hash_tab;
		while (temp->next && recurcmp(name, temp->next->name) > 0)
			temp = temp->next;
		new->next = temp->next;
		temp->next = new;
	}
}

int						hashing(t_hash *hash, char *name)
{
	while (hash)
	{
		if (recurcmp(hash->name, name) == 0)
		{
			if (recurcmp(name, "cd") == 0)
				return (0);
			if (recurcmp(name, "hash") == 0)
				return (0);
			return (1);
		}
		hash = hash->next;
	}
	return (0);
}
