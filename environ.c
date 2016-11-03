/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 19:18:37 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 05:10:55 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int						seter(char *name, char *value, t_shell **shell)
{
	char					*s;
	int						i;
	int						test;

	s = (char *)malloc(sizeof(char) * (ft_strlen(name) + ft_strlen(value) + 2));
	ft_strcat(s, name);
	ft_strcat(s, "=");
	ft_strcat(s, value);
	i = 0;
	test = 1;
	while (i < ft_tablen((*shell)->env) && test)
	{
		if (ft_strncmp((*shell)->env[i], name, ft_strlen(name)) == 0)
		{
			free((*shell)->env[i]);
			(*shell)->env[i] = NULL;
			(*shell)->env[i] = s;
			test = 0;
		}
		i++;
	}
	if (test)
		(*shell)->env = tabtabplus((*shell)->env, s);
	return (0);
}

static void				delete_env(t_shell **shell, char *arg)
{
	int						j;
	int						k;
	char					**env;

	j = 0;
	k = 0;
	env = (char **)malloc(sizeof(char *) * ft_tablen((*shell)->env));
	while (j < ft_tablen((*shell)->env))
	{
		if (ft_strncmp((*shell)->env[j], arg, e_len((*shell)->env[j])) != 0)
			env[k++] = ft_strdup((*shell)->env[j]);
		j++;
	}
	env[k] = 0;
	(*shell)->env = NULL;
	(*shell)->env = env;
}

static int				unseter(char *arg, t_shell **shell)
{
	int						i;
	int						j;

	i = 0;
	j = ft_tablen((*shell)->env);
	while (i < j)
	{
		if (ft_strncmp((*shell)->env[i], arg, e_len((*shell)->env[i]))
				== 0)
		{
			delete_env(shell, arg);
			return (0);
		}
		i++;
	}
	return (0);
}

int						check_env(char **arg, t_shell **shell, int i)
{
	if (ft_tablen(arg) == 1)
		return (ft_env(*shell, 1));
	else if (ft_tablen(arg) > 3 && i == 1)
	{
		putcolor(arg[0], DEFAULT, 2, 0);
		putcolor(" : ", DEFAULT, 2, 0);
		putcolor("Too many arguments.", RED, 2, 1);
		return (1);
	}
	else
	{
		if (i == 1)
		{
			if (ft_tablen(arg) == 2)
				return (seter(arg[1], "", shell));
			else
				return (seter(arg[1], arg[2], shell));
		}
		if (i == 2)
			return (unseter(arg[1], shell));
	}
	return (0);
}
