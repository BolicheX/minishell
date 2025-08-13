/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:02:24 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/13 20:55:20 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Closes a fd in a secure way checking and setting a -1 value.
void	ft_close(int *fd)
{
	if (*fd == -1)
        return ;
	if (close(*fd) == -1)
        ft_perror("error");
    *fd = -1;
}

void	ft_close_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	if (!cmd)
		return;
	if (cmd->in != STDIN_FILENO)
		ft_close(&cmd->in);
	if (cmd->out != STDOUT_FILENO)
		ft_close(&cmd->out);
}

void	ft_clean_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	if (!cmd)
		return;
	if (cmd->in != STDIN_FILENO)
		ft_close(&cmd->in);
	if (cmd->out != STDOUT_FILENO)
		ft_close(&cmd->out);
	ft_free_str_array(cmd->argv);
	free(cmd->path);
	free(cmd);
}

void	ft_clean_parse(t_list *cmd_list, t_cmd *cmd)
{
	if (cmd_list)
	{
		ft_lstclear(&cmd_list, ft_clean_cmd);
		cmd_list = NULL;
	}
	if (cmd)
		ft_clean_cmd(cmd);
}

//Closes every file descriptor in t_ms.
void	ft_close_all(t_ms *ms)
{
	ft_close(&ms->heredoc[0]);
	ft_close(&ms->heredoc[1]);
	ft_lstiter(ms->cmds, ft_close_cmd);
}

//Frees all heap memory in t_ms.
static void ft_free_all(t_ms *ms)
{
	//ft_free_str_array(ms->envp);
	//ft_free_str_array(ms->envp_paths);
	ft_kvl_clear(&ms->env, free);
    free(ms->last_history_entry);
    ft_free_str_array(ms->input_lines);
    free(ms->limiter);
	ft_lstclear(&ms->cmds, ft_clean_cmd);
	ft_lstclear(&ms->tokens, ft_del_token);

	//TODO Los demás campos de ms que estén en heap memory.
}

//Closes every file descriptor and frees all heap memory in t_ms,
//and restores the original terminal configuration.
void    ft_clean_all(t_ms *ms)
{
    ft_close_all(ms);
    ft_free_all(ms);
	//ft_restore_terminal(ms);
}
