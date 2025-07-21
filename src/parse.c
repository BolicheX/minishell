/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:09:27 by jose-jim          #+#    #+#             */
/*   Updated: 2025/07/21 22:20:37 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *ft_new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		ft_perror("malloc");
		return NULL;
	}
	cmd->argv = NULL;
	cmd->argc = 0;
	cmd->path = NULL;
	cmd->in = STDIN_FILENO;
	cmd->out = STDOUT_FILENO;
	return (cmd);
}

int ft_handle_word(t_token *tok, t_cmd *cmd)
{
	char	**new_args;
	char	*arg;
	int		i;

	arg = ft_strdup(tok->value);
	if (!arg)
		return -1;
	new_args = malloc(sizeof(char *) * (cmd->argc + 2));
	if (!new_args)
	{
		free(arg);
		return -1;
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
	return 0;
}

int ft_handle_redir(t_cmd *cmd, t_token *redir_tok, t_list **tokens)
{
	t_token *file_tok;
	int fd;

	fd = -1;
	if (!*tokens || !(*tokens)->content)
		return (ft_perror("syntax error: missing file after redirection"), 0);
	file_tok = (t_token *)(*tokens)->content;
	if (file_tok->type != T_WORD)
		return (ft_perror("syntax error: expected file after redirection"), 0);
	if (!ft_strcmp(redir_tok->value, ">"))
		fd = ft_open_write(file_tok->value, 1);
	else if (!ft_strcmp(redir_tok->value, ">>"))
		fd = ft_open_write(file_tok->value, 0);
	else if (!ft_strcmp(redir_tok->value, "<"))
		fd = ft_open_read(file_tok->value);
	if (redir_tok->value[0] == '<')
		cmd->in = fd;
	else
		cmd->out = fd;
	*tokens = (*tokens)->next;
	return (0);
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

int	ft_handle_pipe(t_cmd **cmd, t_list **cmd_list)
{
	int		fds[2];
	t_list	*node;
	t_cmd	*new_cmd;

	if (pipe(fds) < 0)
	{
		ft_perror("pipe failed");
		return (-1);
	}
	node = ft_lstnew(*cmd);
	if (!node)
		return (-1);
	ft_lstadd_back(cmd_list, node);
	new_cmd = ft_new_cmd();
	if (!new_cmd)
		return (-1);
	(*cmd)->out = fds[1];
	new_cmd->in = fds[0];
	*cmd = new_cmd;
	return (0);
}

int	ft_handle_token(t_token *tok, t_list **tokens, t_cmd **cmd, t_list **cmd_list)
{
	if (tok->type == T_WORD)
		return (ft_handle_word(tok, *cmd));
	else if (tok->type == T_REDIR)
		return (ft_handle_redir(*cmd, tok, tokens));
	else if (tok->type == T_PIPE)
		return (ft_handle_pipe(cmd, cmd_list));
	return (0);
}

t_list *ft_parse(t_list *tokens)
{
	t_list  *cmd_list;
	t_cmd   *cmd;
	t_token *tok;

	cmd_list = NULL;
	cmd = ft_new_cmd();
	if (!cmd)
		return (NULL);
	while (tokens)
	{
		tok = (t_token *)tokens->content;
		tokens = tokens->next;
		if (ft_handle_token(tok, &tokens, &cmd, &cmd_list) < 0)
		{
			ft_clean_parse(NULL, cmd);
			return (NULL);
		}
	}
	if (ft_finalize_cmd(cmd, &cmd_list) < 0)
	{
		ft_clean_parse(cmd_list, cmd);
		return (NULL);
	}
	return (cmd_list);
}
