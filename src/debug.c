/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:24:27 by jose-jim          #+#    #+#             */
/*   Updated: 2025/06/25 21:47:02 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_list(t_list *cmd_list)
{
	int		i;
	t_cmd	*cmd;
	int		cmd_num = 1;

	while (cmd_list)
	{
		cmd = (t_cmd *)cmd_list->content;
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

		cmd_list = cmd_list->next;
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