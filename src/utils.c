/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:19:52 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/18 17:38:25 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_add_history(char *entry, t_ms *ms)
{
    if (ms->last_history_entry && ft_strcmp(ms->last_history_entry, entry) == 0)
        return ;
    free(ms->last_history_entry);
    ms->last_history_entry = ft_strdup(entry);
    add_history(entry);
}

int ft_update_input_lines(char *input, t_ms *ms)
{
    char    **input_lines;

    input_lines = ft_split_empty(input, '\n');
    free(input);
    if (input_lines == NULL)
        return (0);
    ft_free_str_array(ms->input_lines);
    ms->input_lines = input_lines;
    return (1);
}

void    ft_trim_input_lines(int start, t_ms *ms)
{
    char    **temp;

    temp = ms->input_lines;
    ms->input_lines = ft_str_subarray(temp, start, ft_str_arraylen(temp));
    ft_free_str_array(temp);
    if (ms->input_lines == NULL)
        ft_exit_perror(NULL, 1, ms);
}
