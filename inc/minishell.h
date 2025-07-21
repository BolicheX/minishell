/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:35:33 by jose-jim          #+#    #+#             */
/*   Updated: 2025/07/21 22:30:38 by jose-jim         ###   ########.fr       */
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

extern volatile sig_atomic_t	g_signal;//En la ejecución de comandos actualizar con el exit_status del último comando del pipeline.

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
	t_kvl			*env;
	int				termios_ok;
	struct termios	orig_termios;
	int				cmd_prompts_count;
	char			*last_history_entry;
	char			**input_lines;
	char			*limiter;
	int				heredoc[2];
	t_list			*cmds;
	int				status;
	pid_t			pid;
}				t_ms;

/* -------◊		CLEAN	◊------- */
void	ft_close(int *fd);
void	ft_clean_all(t_ms *ms);
void	ft_clean_cmd(void *content);
void	ft_clean_parse(t_list *cmd_list, t_cmd *cmd);

/* -------◊		EXIT	◊------- */
void	ft_perror(char *perror_prefix);
void	ft_exit_perror(char *perror_prefix, int exit_code, t_ms *ms);
int		ft_error(char *cmd, char *arg, char *msg, int exit_code);
void	ft_exit_error(char *cmd, char *arg, char *msg, int exit_code, t_ms *ms);
void	ft_exit_clean(int exit_code, t_ms *ms);

/* -------◊		SIGNALS	◊------- */
void	ft_signals_minishell();
void	ft_signals_heredoc();
void	ft_signals_default();
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

/* -------◊		UTILS	◊------- */
void	ft_add_history(char *entry, t_ms *ms);
void	ft_update_input_lines(char **input_lines, t_ms *ms);

/* -------◊		HEREDOC	◊------- */
int		ft_heredoc(int i, t_ms *ms);

/* -------◊		HEREDOC UTILS	◊------- */
int	ft_heredoc_init(t_list *tokens, t_ms *ms);
void	ft_heredoc_close(t_ms *ms);
void	ft_update_history_entry(char **history_entry_p, char *line, t_ms *ms);
void	ft_trim_input_lines(int start, t_ms *ms);
void	ft_print_heredoc_error(t_ms *ms);

/* -------◊		TOKENS	◊------- */
int		ft_add_token(t_list **tokens, t_token_type type, const char *value);
void	ft_del_token(void *content);

/* -------◊		LEXING	◊------- */
void	ft_lexing(char *line, t_list **tokens);
int	ft_transform_cmd(char *cmd_line, t_ms *ms);

/* -------◊		EXPANDING VARIBALES	◊------- */
int	ft_expand(t_list *tokens, t_ms *ms);

/* -------◊		PARSING	◊------- */
t_list	*ft_parse(t_list *tokens);

/* -------◊		PATHS	◊------- */
void	ft_resolve_paths(t_list *cmd_list, t_ms *ms);

/* -------◊		FILE DESCRIPTORS	◊------- */
int ft_open_read(char *filename);
int ft_open_write(char *filename, int truncate);

/* -------◊		BUILT-INS	◊------- */
int	ft_echo(t_cmd *cmd);
int	ft_pwd(t_cmd *cmd);
int	ft_cd(t_cmd *cmd, t_ms *ms);
int	ft_env(t_cmd *cmd, t_ms *ms);
int	ft_export(t_cmd *cmd, t_ms *ms);

//TODO Quitar este archivo antes de entregar
/* -------◊		DEBUG	◊------- */
void	ft_print_cmd_list(t_list *cmds);
void	ft_print_token(void *node);
void	ft_print_env(t_ms *ms);
void	ft_debug_print_msg(char *message);
void	ft_debug_print_str(char *str, char *pre_msg, char *post_msg);
void	ft_debug_print_array(char **array, char *pre_msg, char *post_msg);
void	ft_debug_print_fd(int fd, char *pre_msg, char *post_msg);

#endif