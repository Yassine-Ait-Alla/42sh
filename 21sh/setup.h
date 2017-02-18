/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 16:36:53 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 07:05:23 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUP_H
# define SETUP_H

typedef struct			s_hist
{
	int					len;
	int					ok;
	int					index;
	int					builtin;
	char				*save;
	char				**hist;
}						t_hist;

typedef struct			s_enable
{
	int					hist;
	int					insert;
	int					paste;
}						t_enable;

typedef struct			s_ccp
{
	char				*str;
	int					beg;
}						t_ccp;

typedef struct			s_setup
{
	int					close_fd;
	int					no_env;
	char				*color;
	char				*color_list[19];
	char				*color_name[19];
	int					test;
	int					prompt;
	char				*cmd;
	int					cp;
	int					prompt_len;
	int					line;
	int					max;
	int					cursor;
	int					pos;
	int					cmdlen;
}						t_setup;

#endif
