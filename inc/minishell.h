/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:35:33 by jose-jim          #+#    #+#             */
/*   Updated: 2025/08/21 13:22:54 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <termios.h>
# include <limits.h>

extern volatile sig_atomic_t	g_signal;

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR,
	T_QUOTE
}				t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}				t_token;

typedef struct s_cmd
{
	char			**argv;
	int				argc;
	char			*path;
	int				in;
	int				out;
}				t_cmd;

typedef struct s_ms
{
	int				is_interactive;
	t_kvl			*env;
	int				termios_ok;//TODO QUITAR si no lo usamos.
	struct termios	orig_termios;//TODO QUITAR si no lo usamos.
	int				lines_count;
	char			*last_history_entry;
	char			**input_lines;
	char			*limiter;
	int				heredoc[2];
	t_list			*tokens;
	t_list			*cmds;
	int				*child_ids;
	int				exit_code;
	pid_t			pid;//TODO QUITAR o ver para qué es
}				t_ms;

/* -------◊		CLEAN	◊------- */
void	ft_close(int *fd);
void	ft_close_cmd(void *content);
void	ft_clean_cmd(void *content);
void	ft_clean_parse(t_list *cmd_list, t_cmd *cmd);
void	ft_close_all(t_ms *ms);
void	ft_clean_all(t_ms *ms);

/* -------◊		EXIT	◊------- */
void	ft_perror(char *perror_prefix, t_ms *ms);
void	ft_exit_perror(char *perror_prefix, int exit_code, t_ms *ms);
int		ft_error(char *cmd, char *arg, char *msg, t_ms *ms);
int		ft_syntax_error(char *token, int exit_code, t_ms *ms);
void	ft_exit_clean(int exit_code, t_ms *ms);

/* -------◊		SIGNALS	◊------- */
void	ft_signals_interactive(void);
void	ft_signals_heredoc(void);
void	ft_signals_default(void);
void    ft_signals_ignore(void);

/* -------◊		INIT	◊------- */
void	ft_init(char *envp[], t_ms *ms);
void	ft_init_termios(t_ms *ms);

/* -------◊		SETUP	◊------- */
void	ft_setup_terminal(t_ms *ms);
void	ft_restore_terminal(t_ms *ms);

/* -------◊		ENV	◊------- */
char	**ft_env_to_array(t_ms *ms);

/* -------◊		UTILS	◊------- */
void	ft_check_signal(t_ms *ms);
void	ft_add_history(char *entry, t_ms *ms);
int		ft_update_input_lines(char *input, t_ms *ms);
void	ft_trim_input_lines(int start, t_ms *ms);
int		ft_del_empty_cmd(t_list **lst);

/* -------◊		HEREDOC	◊------- */
int		ft_heredoc(int i, t_ms *ms);

/* -------◊		HEREDOC UTILS	◊------- */
int		ft_heredoc_init(t_list *tokens, t_ms *ms);
void	ft_update_history_entry(char **history_entry_p, char *line, t_ms *ms);
void	ft_print_heredoc_error(t_ms *ms);
int		ft_get_exit_code_heredoc(int exit_status, t_ms *ms);

/* -------◊		TOKENS	◊------- */
int		ft_token_pipe(t_cmd **cmd, t_ms *ms);
int		ft_token_redir(t_cmd *cmd, t_token *red_tok, t_list **tokens, t_ms *ms);
int		ft_token_word(t_token *tok, t_cmd *cmd);
int		ft_add_token(t_list **tokens, t_token_type type, const char *value);
void	ft_del_token(void *content);

/* -------◊		LEXING	◊------- */
int		ft_lexing(char *line, t_list **tokens, t_ms *ms);
int		skip_quotes(const char *line, int i);
int		lex_operator(const char *line, int i, t_list **tokens);
int		lex_word(const char *line, int i, t_list **tokens);

/* -------◊		EXPANDING VARIBALES	◊------- */
int		ft_handle_quotes(char *str, int *i, char *quote);
char	*ft_replace_var(char *s, t_ms *ms);
int		ft_has_unclosed_quotes(const char *str);
char	*ft_check_expand(char **value, t_ms *ms);
int		ft_expand(t_ms *ms);

/* -------◊		APPENDING EXPANDED VARIABLES	◊------- */
int		ft_append_exit_code(char **result, t_ms *ms, int *i);
int		ft_append_var(t_ms *ms, char **result, char *str, int *i);
int		ft_append_plain_text(char **result, char *str, char quote, int *i);

/* -------◊		PARSING	◊------- */
t_cmd	*ft_new_cmd(t_ms *ms);
int		ft_finalize_cmd(t_cmd *cmd, t_list **cmd_list);
int		ft_handle_token(t_token *tok, t_list **tokens, t_cmd **cmd, t_ms *ms);
void	ft_parse(t_ms *ms);

/* -------◊		PATHS	◊------- */
char	**ft_get_env_path(t_kvl *env);
char	*ft_strjoin_path(const char *path, const char *cmd);
char	*ft_set_path(char *cmd, t_kvl *env);
int		ft_isbuiltin(char *cmd);
int		ft_resolve_paths(t_list **cmd_list, t_ms *ms);

/* -------◊		FILE DESCRIPTORS	◊------- */
int		ft_open_read(char *filename, t_ms *ms);
int		ft_open_write(char *filename, int truncate, t_ms *ms);

/* -------◊		BUILT-INS	◊------- */
int		ft_exit(t_cmd *cmd, int is_subshell, t_ms *ms);
int		ft_echo(t_cmd *cmd);
int		ft_pwd(t_cmd *cmd, t_ms *ms);
int		ft_cd(t_cmd *cmd, t_ms *ms);
int		ft_env(t_ms *ms, t_cmd *cmd);
int		ft_export(t_cmd *cmd, t_ms *ms);
int		ft_unset(t_cmd *cmd, t_ms *ms);

/* -------◊		EXPORT BUILT-IN AUX	◊------- */
void	ft_export_print(t_kvl *sorted, int out_fd);
void	ft_export_no_args(t_cmd *cmd, t_ms *ms);
int		ft_valid_var(const char *str);
int		ft_add_var(char *str, t_ms *ms);

/* -------◊		EXECUTE	◊------- */
void	ft_execute(t_list *cmds, t_ms *ms);
int		ft_execute_if_is_builtin(t_cmd *cmd, int is_subshell, t_ms *ms);
int		ft_get_exit_code(int exit_status);

//TODO Quitar este archivo antes de entregar
/* -------◊		DEBUG	◊------- */
void	ft_print_cmd_list(t_list *cmds);
void	ft_print_token(void *node);
void	ft_print_env(t_ms *ms);
void	ft_debug_print_str(char *message);
void	ft_debug_print_msg(char *message, char *prefix);
void	ft_debug_print_lines(char *str, char *pre_msg, char *post_msg);
void	ft_debug_print_array(char **array, char *pre_msg, char *post_msg);
void	ft_debug_print_fd(int fd, char *pre_msg, char *post_msg);

#endif