/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:19:52 by jescuder          #+#    #+#             */
/*   Updated: 2025/07/20 11:41:03 by jescuder         ###   ########.fr       */
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

void    ft_update_input_lines(char **input_lines, t_ms *ms)
{
    ft_free_str_array(ms->input_lines);
    ms->input_lines = input_lines;
}
