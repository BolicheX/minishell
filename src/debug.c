/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:24:27 by jose-jim          #+#    #+#             */
/*   Updated: 2025/07/20 15:04:47 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_cmd_list(t_list *cmds)
{
	int		i;
	t_cmd	*cmd;
	int		cmd_num = 1;

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
	t_token *token;

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

void	ft_debug_print_msg(char *message)
{
	ft_putendl_fd(message, STDOUT_FILENO);
}

void	ft_debug_print_str(char *str, char *pre_msg, char *post_msg)
{
	ft_debug_print_msg(pre_msg);
	ft_debug_print_msg(str);
	ft_debug_print_msg(post_msg);
}

void	ft_debug_print_array(char **array, char *pre_msg, char *post_msg)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		ft_debug_print_str(array[i++], pre_msg, post_msg);
}

void	ft_debug_print_fd(int fd, char *pre_msg, char *post_msg)
{
	ssize_t bytesRead;
    char buffer[1024];

	if (pre_msg != NULL)
		ft_debug_print_msg(pre_msg);
	while ((bytesRead = read(fd, buffer, 1024)) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
    }
    if (bytesRead == -1) {
        perror("Error al leer");
    }
	if (post_msg != NULL)
		ft_debug_print_msg(post_msg);
}
