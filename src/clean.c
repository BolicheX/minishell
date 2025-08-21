/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:02:24 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/21 21:49:32 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Closes every file descriptor in t_ms.
void	ft_close_all(t_ms *ms)
{
	ft_close(&ms->heredoc[0]);
	ft_close(&ms->heredoc[1]);
	ft_lstiter(ms->cmds, ft_close_cmd);
}

//Frees all heap memory in t_ms.
static void	ft_free_all(t_ms *ms)
{
	ft_kvl_clear(&ms->env, free);
	free(ms->last_history_entry);
	ms->last_history_entry = NULL;
	ft_free_str_array(ms->input_lines);
	ms->input_lines = NULL;
	free(ms->limiter);
	ms->limiter = NULL;
	ft_lstclear(&ms->tokens, ft_del_token);
	ft_lstclear(&ms->cmds, ft_clean_cmd);
	free(ms->child_ids);
	ms->child_ids = NULL;
}

//Closes every file descriptor and frees all heap memory in t_ms.
void	ft_clean_all(t_ms *ms)
{
	ft_close_all(ms);
	ft_free_all(ms);
	rl_clear_history();
	//ft_restore_terminal(ms);
}
