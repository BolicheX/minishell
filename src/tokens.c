/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:40:05 by jose-jim          #+#    #+#             */
/*   Updated: 2025/08/21 12:32:33 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_token_pipe(t_cmd **cmd, t_ms *ms)
{
	int		fds[2];
	t_list	*node;
	t_cmd	*new_cmd;

	/* if ((*cmd)->argc == 0)
		return (ft_syntax_error("|", 2, ms), -1); */
	if (pipe(fds) < 0)
	{
		ft_perror("pipe failed", ms);//TODO ¿No deberíamos terminar minishell aquí, igual que cuando falla malloc(o pipe() en otros sitios)?
		return (-1);
	}
	node = ft_lstnew(*cmd);
	if (!node)
		return (-1);
	ft_lstadd_back(&ms->cmds, node);
	new_cmd = ft_new_cmd(ms);
	if (!new_cmd)
		return (-1);
	(*cmd)->out = fds[1];
	new_cmd->in = fds[0];
	*cmd = new_cmd;
	return (0);
}

int	ft_token_redir(t_cmd *cmd, t_token *red_tok, t_list **tokens, t_ms *ms)
{
	t_token	*file_tok;
	int		fd;

	fd = -1;
	if (!*tokens || !(*tokens)->content)
		return (ft_syntax_error(NULL, 2, ms), -1);
	file_tok = (t_token *)(*tokens)->content;
	if (file_tok->type != T_WORD)
		return (ft_syntax_error(NULL, 2, ms), -1);
	if (!ft_strcmp(red_tok->value, ">"))
		fd = ft_open_write(file_tok->value, 1, ms);
	else if (!ft_strcmp(red_tok->value, ">>"))
		fd = ft_open_write(file_tok->value, 0, ms);
	else if (!ft_strcmp(red_tok->value, "<"))
		fd = ft_open_read(file_tok->value, ms);
	else if (!ft_strcmp(red_tok->value, "<<"))
		fd = ms->heredoc[0];
	ms->heredoc[0] = -1;
	if (red_tok->value[0] == '<')
		cmd->in = fd;
	else
		cmd->out = fd;
	*tokens = (*tokens)->next;
	return (0);
}

int	ft_token_word(t_token *tok, t_cmd *cmd)
{
	char	**new_args;
	char	*arg;
	int		i;

	arg = ft_strdup(tok->value);
	if (!arg)
		return (-1);
	new_args = malloc(sizeof(char *) * (cmd->argc + 2));
	if (!new_args)
	{
		free(arg);
		return (-1);
	}
	i = 0;
	while (i < cmd->argc)
	{
		new_args[i] = cmd->argv[i];
		i++;
	}
	new_args[cmd->argc] = arg;
	new_args[cmd->argc + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_args;
	cmd->argc++;
	return (0);
}

int	ft_add_token(t_list **tokens, t_token_type type, const char *value)
{
	t_token	*token;
	t_list	*node;

	token = malloc(sizeof(t_token));
	if (!token)
		return (0);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (0);
	}
	node = ft_lstnew(token);
	if (!node)
	{
		free(token->value);
		free(token);
		return (0);
	}
	ft_lstadd_back(tokens, node);
	return (1);
}

void	ft_del_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->value);
	free(token);
}
