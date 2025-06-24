/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:35:33 by jose-jim          #+#    #+#             */
/*   Updated: 2025/06/24 18:02:06 by jescuder         ###   ########.fr       */
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
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

// typedef struct s_env
// {
// 	char			*key;
// 	char			*value;
// 	struct s_env	*next;
// }	t_env;

typedef struct s_cmd
{
	char			**argv;
	char			*path;
	int				in;
	int				out;
	struct s_cmd	*next;
}		t_cmd;

typedef struct s_ms
{
	t_cmd	*cmd_list;
	//t_env	*env_list;
	char	**envp;
	char	**envp_paths;
	int		cmd_line_num;
	int		status;
	pid_t	pid;
}		t_ms;

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
t_token	*ft_new_token(t_token_type type, char *value);
void	ft_add_token(t_token **list, t_token *new);
void	ft_print_tokens(t_token *tokens);

/* -------◊		LEXING	◊------- */
int	ft_transform_cmd(char *cmd_line, t_ms *ms);


#endif