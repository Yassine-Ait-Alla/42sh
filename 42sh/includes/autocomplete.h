/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:27:17 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 15:59:58 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCOMPLETE_H
# define AUTOCOMPLETE_H

# include "full_sh.h"

# define EQU_IS_DIRECTORY (all->equ2find[ft_strlen(all->equ2find) - 1] == '/')

typedef struct s_all		t_all;
typedef struct s_clist		t_clist;
typedef struct s_select		t_select;

/*
*** ======================= autocomplete.c
*/

char		*cut_equ(char *s);
char		*cut_dir(char *s);
void		display_elems(t_all *all, t_clist *lst);
void		search_autocomplete(t_all *all);

/*
*** ======================= autocomplete_tools.c
*/

void		ask_for_big_display(t_all *all);
int			check_prev_directory(char *s);
void		cut_cmd_equ(t_all *all);

/*
*** ======================= autocomplete_tools_2.c
*/

int			find_maxlen_elem(t_clist *lst);
int			define_nb_files_by_row(t_all *all, t_clist *lst);
int			no_spaces(t_cmd *lst);
void		add_spaces(t_all *all, int tmp_len, int ct);

/*
*** ======================= binary_search.c
*/

void		search_bin_path(t_all *all);

/*
*** ======================= directory_search.c
*/

void		open_path_directory(t_all *all, char *dir2open);
void		swap_elems(t_select *a, t_select *b);
void		sort_name(t_select **lst);

/*
*** ======================= equality_search.c
*/

char		*cut_directory_in_path(char *equ2find);
char		*open_right_directory(t_all *all, char *equ2find);
void		search_equality(t_all *all, char *equ2find, char *dir2open);
void		results_analysis_equ(t_all *all, char *equ2find);
void		list_dir_equ(t_all *all);

/*
*** ======================= equality_search_tools.c
*/

char		*update_tmp_cmd(t_all *all, char *str2add, int len2skip);
int			is_dir(t_all *all, char *s);
int			check_next_slash(char *s);
int			directory_in_path(t_all *all, char *equ2find);
int			count_nb_dir(char *s);

#endif
