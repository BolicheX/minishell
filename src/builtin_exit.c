/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:17:15 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/21 13:18:05 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  ft_parse_exit_code(char *str)
{
    unsigned long   result;
    int             sign;

    result = 0;
    sign = 1;
    while (ft_isspace(*str))
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str++ == '-')
            sign = -1;
    }
    if (ft_isdigit(*str) == 0)
        return (-1);
    while (ft_isdigit(*str))
    {
        if (result > ((unsigned long)LONG_MAX + 1 - (*str - '0')) / 10)
            return (-1);
        result = result * 10 + (*str++ - '0');
    }
    while (ft_isspace(*str))
        str++;
    if ((*str != '\0') || (sign == 1 && result > (unsigned long)LONG_MAX))
        return (-1);
    return ((long)result * sign % 256);
}

int ft_exit(t_cmd *cmd, int is_subshell, t_ms *ms)
{
    int     exit_code;

    if (is_subshell == 0 && ms->is_interactive == 1)
        ft_putendl_fd("exit", STDERR_FILENO);
    if (cmd->argc == 1)
       ft_exit_clean(ms->exit_code, ms);
    exit_code = ft_parse_exit_code(cmd->argv[1]);
    if (exit_code == -1)
    {
        ft_error("exit", cmd->argv[1], "numeric argument required", ms);
        ft_exit_clean(2, ms);
    }
    if (cmd->argc > 2)
    {
        ft_error("exit", NULL, "too many arguments", ms);
        return (1);
    }
    ft_exit_clean(exit_code, ms);
    return (0);
}
