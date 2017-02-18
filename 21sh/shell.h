/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 12:38:07 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 14:22:34 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include "colors.h"
# include "tree.h"
# include "def.h"
# include "lex.h"
# include "setup.h"
# include <dirent.h>
# include <sys/wait.h>
# include <term.h>
# include <errno.h>
# include <termcap.h>
# include <termios.h>
# include <signal.h>
# include <curses.h>
# include <sys/ioctl.h>

typedef struct			s_trial
{
	struct termios		term;
	int					lins;
	int					cols;
}						t_trial;

typedef struct			s_hash
{
	int					time;
	char				*name;
	char				*path;
	struct s_hash		*next;
}						t_hash;

typedef struct			s_shell
{
	int					heredoc;
	char				*end_of_message;
	char				*document;
	int					test;
	int					status;
	char				**env;
	char				*home;
	char				*path;
	char				*pwd;
	char				*old_pwd;
	char				*cmd;
	int					*select;
	char				*builtin[11];
	t_ccp				*ccp;
	t_hist				*hist;
	t_hash				*hash;
	t_ree				*ast;
	t_oken				*token;
	t_setup				setup;
	t_enable			enable;
	t_trial				trial;
}						t_shell;

int						heredoc(t_shell *shell, char **arg);
char					*split_doc(char **arg, int i, char *doc);

void					prompter_1(t_shell *shell);
void					prompter_2(t_shell *shell);
int						change_prompt(t_shell *shell);
int						change_color(t_shell *shell, char **arg);
void					initcolor(t_shell *shell);
void					init_name(t_shell *shell);

int						get_cmd(t_shell *shell, int const fd, char **line);
char					*normal(t_shell *shell, char *str, int i);
char					*paste_str(t_shell *shell);
void					copy_str(t_shell *shell);
void					count(t_shell *shell);
void					selection(t_shell *shell);
void					display(t_shell *shell, char *str);

void					go_down(t_shell *shell);
void					go_left(t_shell *shell);
void					go_right(t_shell *shell);
void					clear_line(t_shell *shell);
void					cline(t_shell *shell);
char					*reg_prompt(t_shell *shell, char *str, int j);
char					*regulator(t_shell *shell, char buf[4], char *save);
char					*regulate(char *save, char buf[4], t_shell *shell);
void					syntax_hist(t_shell *shell, char **arg);
void					historic(char buf[4], t_shell *shell);
int						display_historic(t_shell *shell, char **arg);

char					*backspacer(t_shell *shell, char *s);
void					the_arrow(t_shell *shell, char buf[4]);
void					key_checker(t_shell *shell, char buf[4]);
void					move_cursor(char buf[4], t_shell *shell);
void					reset_command(t_shell *shell);
void					liner(t_shell *shell);

t_oken					*create_token(char *cmd, t_shell *shell);
t_ree					*command_node(t_ree *papa, t_way w);
t_ree					*command_seed(t_ree *papa, t_way w, t_oken *token);
t_ree					*node_seed(t_ree *papa, t_way w, t_reetype type);
t_ree					*plant(t_oken *token, t_ree *papa, t_way w);

t_shell					*reset(int i, t_shell *shell);
int						tputchar(int c);
void					sig_catcher(int i);
void					signaler(void);
void					command_arg(t_ree *node, t_oken **token);
void					cmd_son(t_cmd *c, t_shell *shell, int fdin, int fdout);
int						process(t_ree *tree, t_shell *shell, int c);
void					free_env(char ***env);
int						seter(char *name, char *value, t_shell **shell);
int						check_env(char **arg, t_shell **shell, int i);
int						ft_cd(t_shell **shell, char **arg);
void					free_cmd(t_cmd *c);
void					free_tree(t_ree *tree);
void					ft_exit(t_shell **shell, char **arg);
int						cd_error(char *path, char *arg);
int						ft_env(t_shell *shell, int fdout);
int						hasher(t_shell *shell, int fdout);
int						built(char **arg, t_shell *shell, int fdout, int i);
int						is_built(char *arg, t_shell *shell);
int						path_cmd(t_ree *tree, t_shell *shell, int i, int fdout);
int						cmd_proc(t_ree *tree, t_shell *shell, int i);
void					pipe_son(t_ree *tree, t_shell *shell, int *i);
void					prompter(t_shell *shell);
void					prompt(t_shell *shell);
t_shell					*init_all(char **environ);
void					recup(t_hash **hash_tab, char *name, char *path);
int						terminit(t_shell *shell);
int						termclose(t_shell *shell);
void					puterm(char *tc);
int						hashing(t_hash *hash, char *name);

#endif
