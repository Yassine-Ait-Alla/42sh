/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_2_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/03 18:29:35 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:04:50 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

t_dlist2	*create_cmd_dlst(void)
{
	t_dlist2	*new;

	if (!(new = (t_dlist2 *)malloc(sizeof(t_dlist2))))
		return (NULL);
	else
	{
		new->lenght = 0;
		new->tail = NULL;
		new->head = NULL;
	}
	return (new);
}

t_cmd		*dlst_cmd_new(char c)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new)
	{
		new->c = c;
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}

void		swap_elems_cmd(t_cmd *a, t_cmd *b)
{
	char	tmp;

	tmp = a->c;
	a->c = b->c;
	b->c = tmp;
}

int			len_lst_cmd(t_cmd *lst)
{
	t_cmd		*nav;
	int			ret;

	nav = lst;
	ret = 0;
	if (nav)
	{
		while (nav)
		{
			ret++;
			nav = nav->next;
		}
	}
	return (ret);
}

int			update_list2(t_dlist2 *lst, t_cmd *elem)
{
	if (!elem->next && elem->prev)
	{
		elem->c = 0;
		lst->tail = elem->prev;
		lst->tail->next = NULL;
	}
	else if (!elem->prev && elem->next)
	{
		elem->c = 0;
		lst->head = elem->next;
		lst->head->prev = NULL;
	}
	else
	{
		elem->c = 0;
		elem->prev->next = elem->next;
		elem->next->prev = elem->prev;
	}
	return (1);
}
