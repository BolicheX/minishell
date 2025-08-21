/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:24:27 by jose-jim          #+#    #+#             */
/*   Updated: 2025/08/21 21:50:28 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_cmd_list(t_list *cmds)
{
	int		i;
	t_cmd	*cmd;
	int		cmd_num;

	cmd_num = 1;
	while (cmds)
	{
		cmd = (t_cmd *)cmds->content;
		printf("Command #%d:\n", cmd_num++);
		printf("  argv: ");
		if (cmd->argv)
		{
			for (i = 0; cmd->argv[i]; i++)
				printf("'%s' ", cmd->argv[i]);
		}
		else
			printf("(null)");
		printf("\n");
		printf("  path: %s\n", cmd->path ? cmd->path : "(null)");
		printf("  in: %d\n", cmd->in);
		printf("  out: %d\n", cmd->out);

		cmds = cmds->next;
	}
}

void	ft_print_token(void *node)
{
	t_token	*token;

	token = (t_token *)node;
	if (token->type == T_WORD)
		printf("[WORD]  [%s]\n", token->value);
	else if (token->type == T_REDIR)
		printf("[REDIR] [%s]\n", token->value);
	else if (token->type == T_PIPE)
		printf("[PIPE]  [%s]\n", token->value);
}

static void	ft_print_env_internal(char *key, void *value)
{
	printf("Key: %s\n", key);
	printf("Value: %s\n", (char *) value);
}

//Para probar que se están inicializando bien las variables de entorno.
void	ft_print_env(t_ms *ms)
{
	printf("%s", "Variables de entorno:\n");
	ft_kvl_iter(ms->env, ft_print_env_internal);
}

void	ft_debug_print_str(char *message)
{
	ft_putendl_fd(message, STDERR_FILENO);
}

void	ft_debug_print_msg(char *message, char *prefix)
{
	if (prefix != NULL)
		ft_putstr_fd(prefix, STDERR_FILENO);
	ft_debug_print_str(message);
}

void	ft_debug_print_lines(char *str, char *pre_msg, char *post_msg)
{
	ft_debug_print_str(pre_msg);
	ft_debug_print_str(str);
	ft_debug_print_str(post_msg);
}

void	ft_debug_print_array(char **array, char *pre_msg, char *post_msg)
{
	int	i;

	ft_debug_print_str(pre_msg);
	i = 0;
	while (array[i] != NULL)
		ft_debug_print_str(array[i++]);
	ft_debug_print_str(post_msg);
}

void	ft_debug_print_fd(int fd, char *pre_msg, char *post_msg)
{
	ssize_t bytesRead;
    char buffer[1024];

	if (pre_msg != NULL)
		ft_debug_print_str(pre_msg);
	while ((bytesRead = read(fd, buffer, 1024)) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
    }
    if (bytesRead == -1) {
        perror("Error al leer");
    }
	if (post_msg != NULL)
		ft_debug_print_str(post_msg);
}
