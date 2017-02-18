/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 10:17:41 by lubaujar          #+#    #+#             */
/*   Updated: 2016/05/30 17:38:20 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"
#define ERR_ENV "\nusage: env [-i] [name=value ...] [utility [argument ...]]\n"

int		check_env_error(char **tmp)
{
	if (ft_strcmp(tmp[0], "env"))
	{
		write_error(tmp[0]);
		return (0);
	}
	if (tmp[1] && tmp[1][0] == '-' && ft_strcmp(tmp[1], "-i"))
	{
		ft_putstr("env: illegal option -- ");
		ft_putstr(tmp[1]);
		ft_putstr(ERR_ENV);
		return (0);
	}
	return (1);
}

char	**realloc_env_array(t_dlist *env)
{
	t_node	*nav;
	char	**ret;
	int		ct;

	nav = env->head;
	ct = 0;
	if (!(ret = (char**)malloc(sizeof(char *) * env->lenght + 1)))
		error("MALLOC");
	if (nav && ret)
	{
		while (nav)
		{
			ret[ct] = ft_strdup(nav->s);
			nav = nav->next;
			ct++;
		}
		ret[ct] = NULL;
	}
	return (ret);
}

void	update_env(t_all *all, char *s)
{
	t_node	*nav;

	nav = all->env->head;
	if (nav)
	{
		while (nav)
		{
			if (!ft_strncmp(nav->s, all->tmp_var_env, \
				ft_strlen(all->tmp_var_env)))
			{
				ft_strdel(&nav->s);
				nav->s = ft_strdup(s);
				return ;
			}
			nav = nav->next;
		}
	}
}

int		good_env_formatting(char *s)
{
	char	*tmp;

	tmp = ft_strchr(s, '=');
	if (*(tmp - 1) && ft_isprint(*(tmp - 1))
		&& *tmp == '=' && *(tmp + 1) && ft_isprint(*(tmp + 1)))
		return (1);
	return (0);
}

int		symbol_in_cmd(char *s, int symbol)
{
	int	ct;
	int	ret;

	ct = 0;
	ret = 0;
	if (s && s[ct] && symbol)
	{
		while (s && s[ct])
		{
			if (s[ct] == symbol)
				ret++;
			ct++;
		}
	}
	if (ret == 1)
		return (1);
	return (0);
}
