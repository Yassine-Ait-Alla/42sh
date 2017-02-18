/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 04:57:56 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/11 06:25:36 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char					*normal(t_shell *shell, char *str, int i)
{
	SET.cursor += ft_strlen(CCP->str);
	return (reg_prompt(shell, str, i));
}
