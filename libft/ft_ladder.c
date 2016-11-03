/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ladder.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 16:15:49 by yaitalla          #+#    #+#             */
/*   Updated: 2015/12/13 13:22:48 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ladder(t_list *lst, char *content)
{
	t_list			*temp;
	size_t			i;

	temp = lst;
	while (temp->next)
		temp = temp->next;
	i = 0;
	while (content[i])
		i++;
	temp->next = ft_lstnew(content, i);
}
