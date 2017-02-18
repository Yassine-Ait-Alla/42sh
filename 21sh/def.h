/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaitalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 16:10:35 by yaitalla          #+#    #+#             */
/*   Updated: 2016/07/15 10:36:26 by yaitalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_H
# define DEF_H

# define TEST		SET.test = 1
# define EOM		end_of_message

# define COLOR		shell->color
# define BUF		buf[0]
# define CURCHAR	(SET.cmd[SET.cursor])
# define SPACE		(CURCHAR == ' ' || CURCHAR == '\t')

# define SEL		shell->select
# define SEL_CHECK	(SET.cp == 1 && !K_LEFT && !K_RIGHT)
# define SELECT		(BUF == -62 && buf[1] == -96)
# define CTRL_C		(buf[0] == 3 && buf[1] == 0 && buf[2] == 0)
# define CTRL_D		(buf[0] == 4 && buf[1] == 0 && buf[2] == 0)
# define C			(buf[0] == 27 && buf[1] == 27 && buf[2] == 91)
# define C_LEFT		(C && buf[3] == 68)
# define C_RIGHT	(C && buf[3] == 67)
# define C_UP		(C && buf[3] == 65)
# define C_DOWN		(C && buf[3] == 66)

# define K_SPACE	(buf[0] == 32 && !buf[1] && !buf[2])
# define K_END		(buf[0] == 27 && buf[1] == 91 && buf[2] == 70)
# define K_ENTER	(buf[0] == 10 && !buf[1] && !buf[2])
# define KEYZ		(!ARROW && !SPECIAL)

# define PR			(buf[0] == 96 || buf[0] == 34 || buf[0] == 39)
# define TZ			(buf[0] == 91 || buf[0] == 123 || buf[0] == 40)
# define PT			(buf[0] == 93 || buf[0] == 125 || buf[0] == 41)
# define PTZ		shell->prtz
# define PRTZ		(PR || TZ || PT)

# define HST		shell->hist
# define CMD		HST->hist[HST->index]
# define CURR		shell->select[SET.cursor]
# define HISTORIC	(CURR >= 0 && CURR < ft_tablen(shell->hist))
# define HST_EDIT	(ENABLE.hist == 1 && PRINTABLE == 1)
# define BAKSP		cursor[2]

# define ENABLE		shell->enable
# define SET		shell->setup
# define TT			shell->trial
# define COL		shell->trial.cols
# define CCP_OK		(!ENABLE.ccp && CCP_MODE && SET.cursor < SET.cmdlen)
# define CCP		shell->ccp

# define K_UP		(buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
# define K_DOWN		(buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
# define K_RIGHT	(buf[0] == 27 && buf[1] == 91 && buf[2] == 67)
# define K_LEFT		(buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
# define ARROW		(K_LEFT || K_RIGHT || K_DOWN || K_UP)

# define PRINTABLE	((int)buf[0] != 27 && (int)buf[0] !=127 && (int)buf[0] != 5)

# define COPY		(buf[0] == -61 && buf[1] == -89)
# define PASTE		(buf[0] == -30 && buf[1] == -120 && buf[2] == -102)
# define PASTE_OK	(PASTE && ENABLE.paste == 1)

# define K_ECHAP	(buf[0] == 27 && !buf[1] && !buf[2])
# define K_BAKSP	(buf[0] == 127 && !buf[1] && !buf[2])
# define K_DEL		(buf[0] == 126 && buf[1] == 91 && buf[2] == 51)
# define K_HOME		(buf[0] == 27 && buf[1] == 91 && buf[2] == 72)
# define K_END		(buf[0] == 27 && buf[1] == 91 && buf[2] == 70)

# define CONTROL	(buf[0] == 23 && buf[1] == 0 && buf[2] == 0 && buf[3] == 0)
# define COPY_PASTE	(COPY || PASTE)
# define REGULAR	(!ARROW && buf[0] != 9 && PRINTABLE && !COPY_PASTE)
# define SPECIAL	(K_BAKSP || K_ECHAP || K_DEL || K_HOME || K_END || CONTROL)

# define S			cmd[i]
# define P			cmd[i + ret]
# define HEREDOC	(S == '<' && cmd[i - 1] != '<' && cmd[i + 1] != '<')
# define S_CHECK	(S == '|' || S == ';' || HEREDOC || S == '>' || S == '&')
# define S_CHECK_FD	(S_CHECK || S == '1' || S == '2')
# define SPCHECK	(P == '|' || P == ';' || P == '>' || P == '&')
# define REDIR_LL	(temp->type == REDIR_L && temp->next->type == REDIR_L)
# define ERR_1		(!temp->next || (!temp->prev && !REDIR_LL))
# define ERR_2		(temp->next->type == SEMICOL || temp->prev->type == SEMICOL)
# define PARS_ERR	(ERR_1 || ERR_2)

# define TOKEN		shell->token
# define B_TREE		shell->ast
# define STATUS		shell->status
# define TYPE		tree->type
# define ENV		shell->env[i]
# define PAPA		temp->parent
# define OUT		cmd->fdout.type
# define COMMAND	cmd->fdout.file
# define OK			(REGULAR && !SPECIAL)

#endif
