/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_search.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 00:48:15 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:10:22 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void	open_path_directory(t_all *all, char *dir2open)
{
	DIR			*entry;
	t_dirent	*dirp;

	all->tmp_cmd = ft_strdup(all->cmd);
	all->list_dir = create_clst();
	if (!(entry = opendir(dir2open)))
		return ;
	else
	{
		while ((dirp = readdir(entry)) && dirp->d_name[0] != '\0')
		{
			if (ft_strcmp(dirp->d_name, ".") && ft_strcmp(dirp->d_name, ".."))
				clst_add_elem_back(all->list_dir, \
									clst_create_elem(dirp->d_name));
		}
	}
	(all->list_dir->lenght > 0) ? display_elems(all, all->list_dir) : NULL;
	closedir(entry);
	del_clist(&all->list_dir);
	all->already_autocomplete = 1;
	loop(all);
}

void	swap_elems(t_select *a, t_select *b)
{
	char	*tmp_s;

	tmp_s = ft_strdup(a->arg);
	ft_strdel(&a->arg);
	a->arg = ft_strdup(b->arg);
	ft_strdel(&b->arg);
	b->arg = ft_strdup(tmp_s);
	ft_strdel(&tmp_s);
}

void	sort_name(t_select **lst)
{
	t_select		*nav;
	int				i;

	nav = *lst;
	i = len_clst(*lst);
	if (nav)
	{
		while (i--)
		{
			nav = *lst;
			while (nav && nav->next)
			{
				if (ft_strcmp(nav->arg, nav->next->arg) > 0)
					swap_elems(nav, nav->next);
				nav = nav->next;
			}
		}
	}
}
