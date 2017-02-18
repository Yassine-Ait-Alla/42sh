/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <yaitalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 18:04:19 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 14:57:33 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	size_t		i;
	char		*result;

	i = ft_countnbr(n);
	if (n < 0)
	{
		n = -n;
		result = (char *)malloc(sizeof(char) * i);
		result[0] = '-';
		i++;
	}
	else
		result = (char *)malloc(sizeof(char) * i);
	result[i] = '\0';
	if (n == 0)
		result[0] = '0';
	while (i-- && n)
	{
		result[i] = (n % 10) + '0';
		n /= 10;
	}
	return (result);
}
