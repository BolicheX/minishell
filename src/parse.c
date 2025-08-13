/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:09:27 by jose-jim          #+#    #+#             */
/*   Updated: 2025/08/13 22:08:50 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_new_cmd(t_ms *ms)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		ft_exit_perror("malloc", 1, ms);
		return (NULL);
	}
	cmd->argv = NULL;
	cmd->argc = 0;
	cmd->path = NULL;
	cmd->in = STDIN_FILENO;
	cmd->out = STDOUT_FILENO;
	return (cmd);
}

int	ft_finalize_cmd(t_cmd *cmd, t_list **cmd_list)
{
	t_list	*last;

	last = ft_lstnew(cmd);
	if (!last)
		return (-1);
	ft_lstadd_back(cmd_list, last);
	return (0);
}

int	ft_handle_token(t_token *tok, t_list **tokens, t_cmd **cmd, t_ms *ms)
{
	if (tok->type == T_WORD)
		return (ft_token_word(tok, *cmd));
	else if (tok->type == T_REDIR)
		return (ft_token_redir(*cmd, tok, tokens, ms));
	else if (tok->type == T_PIPE)
		return (ft_token_pipe(cmd, ms));
	return (0);
}

void	ft_parse(t_ms *ms)
{
	t_cmd	*cmd;
	t_token	*tok;
	t_list *tokens;

	tokens = ms->tokens;
	cmd = ft_new_cmd(ms);
	if (!cmd)
		return ;
	while (tokens)
	{
		tok = (t_token *)tokens->content;
		tokens = tokens->next;
		if (ft_handle_token(tok, &tokens, &cmd, ms) < 0)
		{
			ft_clean_parse(NULL, cmd);
			return ;
		}
	}
	if (ft_finalize_cmd(cmd, &ms->cmds) < 0)
	{
		ft_clean_parse(ms->cmds, cmd);
		return ;
	}
}
