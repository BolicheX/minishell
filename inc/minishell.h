/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:35:33 by jose-jim          #+#    #+#             */
/*   Updated: 2025/06/26 18:03:09 by jescuder         ###   ########.fr       */
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


typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR,
	T_QUOTE
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}	t_token;

typedef struct s_cmd
{
	char			**argv;
	char			*path;
	int				in;
	int				out;
}		t_cmd;

typedef struct s_ms
{
	t_list	*cmds;
	t_kvl	*env;
	int		cmd_lines_num;
	int		status;
	pid_t	pid;
}		t_ms;

/* -------◊		INIT	◊------- */
void    ft_init(char *envp[], t_ms *ms);
void    ft_init_env(char *envp[], t_ms *ms);

/* -------◊		CLEAN	◊------- */
void	ft_close(int *fd);
void	ft_free_str_array(char **array);
void	ft_clean_all(t_ms *ms);

/* -------◊		EXIT	◊------- */
void	ft_perror(char *perror_prefix);
void	ft_exit_perror(char *perror_prefix, int exit_code, t_ms *ms);
void	ft_exit_error(char *message, int exit_code, t_ms *ms);
void	ft_exit_clean(int exit_code, t_ms *ms);

/* -------◊		TOKENS	◊------- */
int		ft_add_token(t_list **tokens, t_token_type type, const char *value);
void	ft_del_token(void *content);

/* -------◊		LEXING	◊------- */
int	ft_transform_cmd(char *cmd_line, t_ms *ms);

/* -------◊		EXPANDING VARIBALES	◊------- */
int	ft_expand(t_list *tokens, t_ms *ms);

/* -------◊		PARSING	◊------- */
//t_list	*ft_parse(t_list *tokens);

/* -------◊		DEBUG	◊------- */
void	ft_print_cmd_list(t_list *cmds);
void	ft_print_token(void *node);
void	ft_print_env(t_ms *ms);

#endif