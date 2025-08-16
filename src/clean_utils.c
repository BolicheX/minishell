/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:06:01 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/15 19:07:19 by jescuder         ###   ########.fr       */
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
