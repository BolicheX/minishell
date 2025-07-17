/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:35:33 by jose-jim          #+#    #+#             */
/*   Updated: 2025/07/17 18:15:15 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <termios.h>

typedef enum	e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR,
	T_QUOTE
}				t_token_type;

typedef struct	s_token
{
	char			*value;
	t_token_type	type;
}				t_token;

typedef struct	s_cmd
{
	char			**argv;
	int				argc;
	char			*path;
	int				in;
	int				out;
}				t_cmd;

typedef struct	s_ms
{
	int				termios_ok;
	struct termios	orig_termios;
	int				cmd_lines_num;
	t_list			*cmds;
	t_kvl			*env;
	int				status;
	pid_t			pid;
}				t_ms;

/* -------◊		CLEAN	◊------- */
void	ft_close(int *fd);
void	ft_free_str_array(char **array);
void	ft_clean_all(t_ms *ms);
void	ft_clean_cmd(void *content);
void	ft_clean_parse(t_list *cmd_list, t_cmd *cmd);

/* -------◊		EXIT	◊------- */
void	ft_perror(char *perror_prefix);
void	ft_exit_perror(char *perror_prefix, int exit_code, t_ms *ms);
void	ft_error(char *cmd, char *arg, char *msg, int exit_code);
void	ft_exit_error(char *msg, int exit_code, t_ms *ms);
void	ft_exit_clean(int exit_code, t_ms *ms);

/* -------◊		SIGNALS	◊------- */
void    ft_prompt_signal_handler(int sig);
void	ft_restore_child_signals();
void	ft_print_signal_terminated(int status);

/* -------◊		INIT	◊------- */
void    ft_init(char *envp[], t_ms *ms);
void	ft_init_termios(t_ms *ms);

/* -------◊		SETUP	◊------- */
void	ft_setup_terminal(t_ms *ms);
void	ft_restore_terminal(t_ms *ms);
void	ft_setup_signals();

/* -------◊		ENV	◊------- */
//char	**ft_get_env_array(t_ms *ms);

/* -------◊		TOKENS	◊------- */
int		ft_add_token(t_list **tokens, t_token_type type, const char *value);
void	ft_del_token(void *content);

/* -------◊		LEXING	◊------- */
int	ft_transform_cmd(char *cmd_line, t_ms *ms);

/* -------◊		EXPANDING VARIBALES	◊------- */
int	ft_expand(t_list *tokens, t_ms *ms);

/* -------◊		PARSING	◊------- */
t_list	*ft_parse(t_list *tokens);
void	ft_clean_parse(t_list *cmd_list, t_cmd *cmd);

/* -------◊		PATHS	◊------- */
void	ft_resolve_paths(t_list *cmd_list, t_ms *ms);

/* -------◊		FILE DESCRIPTORS	◊------- */
int ft_open_read(char *filename);
int ft_open_write(char *filename, int truncate);

/* -------◊		BUILT-INS	◊------- */
int	ft_echo(t_cmd *cmd);
int	ft_pwd(t_cmd *cmd);
int	ft_cd(t_cmd *cmd, t_ms *ms);

/* -------◊		DEBUG	◊------- */
void	ft_print_cmd_list(t_list *cmds);
void	ft_print_token(void *node);
void	ft_print_env(t_ms *ms);


#endif