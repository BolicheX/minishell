/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:19:52 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/21 22:49:58 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_signal(t_ms *ms)
{
	if (g_signal != 0)
	{
		ms->exit_code = g_signal;
		g_signal = 0;
	}
}

void	ft_add_history(char *entry, t_ms *ms)
{
	if (ms->last_history_entry && ft_strcmp(ms->last_history_entry, entry) == 0)
		return ;
	free(ms->last_history_entry);
	ms->last_history_entry = ft_strdup(entry);
	add_history(entry);
}

int	ft_update_input_lines(char *input, t_ms *ms)
{
	char	**input_lines;

	input_lines = ft_split_empty(input, '\n');
	free(input);
	if (input_lines == NULL)
		return (0);
	ft_free_str_array(ms->input_lines);
	ms->input_lines = input_lines;
	return (1);
}

void	ft_trim_input_lines(int start, t_ms *ms)
{
	char	**temp;

	temp = ms->input_lines;
	ms->input_lines = ft_str_subarray(temp, start, ft_str_arraylen(temp));
	ft_free_str_array(temp);
	if (ms->input_lines == NULL)
		ft_exit_perror(NULL, 1, ms);
}

int	ft_del_empty_cmd(t_list **lst)
{
	t_list	*curr;
	t_list	*prev;
	t_list	*next;
	t_cmd	*cmd;

	curr = *lst;
	prev = NULL;
	while (curr)
	{
		cmd = (t_cmd *)curr->content;
		next = curr->next;
		if (!cmd || !cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
		{
			if (prev)
				prev->next = next;
			else
				*lst = next;
			ft_lstdelone(curr, ft_clean_cmd);
		}
		else
			prev = curr;
		curr = next;
	}
	return (*lst == NULL);
}
