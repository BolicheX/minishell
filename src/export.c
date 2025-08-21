/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:37:32 by jose-jim          #+#    #+#             */
/*   Updated: 2025/08/21 13:20:26 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_print(t_kvl *sorted, int out_fd)
{
	while (sorted)
	{
		ft_putstr_fd("declare -x ", out_fd);
		if (sorted->key)
			ft_putstr_fd(sorted->key, out_fd);
		if (sorted->value)
		{
			ft_putstr_fd("=\"", out_fd);
			ft_putstr_fd(sorted->value, out_fd);
			ft_putchar_fd('"', out_fd);
		}
		ft_putchar_fd('\n', out_fd);
		sorted = sorted->next;
	}
}

void	ft_export_no_args(t_cmd *cmd, t_ms *ms)
{
	t_kvl	*clone;
	t_kvl	*sorted;

	clone = ft_kvl_strclone(ms->env);
	if (!clone)
		ft_exit_perror("export", 1, ms);
	sorted = ft_kvl_alphasort(clone);
	ft_export_print(sorted, cmd->out);
	ft_kvl_clear(&sorted, free);
}

int	ft_valid_var(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_add_var(char *str, t_ms *ms)
{
	char	*key;
	char	*value;
	char	*eq;

	eq = ft_strchr(str, '=');
	if (eq)
	{
		key = ft_substr(str, 0, eq - str);
		value = ft_strdup(eq + 1);
	}
	else
	{
		key = ft_strdup(str);
		value = NULL;
	}
	if (!key || (eq && !value))
	{
		free(key);
		free(value);
		ft_error("export", str, "memory allocation error", ms);
		return (1);
	}
	ft_kvl_set(&ms->env, key, value);
	free(key);
	return (0);
}

int	ft_export(t_cmd *cmd, t_ms *ms)
{
	int	i;

	if (cmd->argc == 1)
	{
		ft_export_no_args(cmd, ms);
		return (0);
	}
	i = 1;
	while (cmd->argv[i])
	{
		if (!ft_valid_var(cmd->argv[i]))
		{
			ft_error("export", cmd->argv[i], "not a valid identifier", ms);
			i++;
			continue ;
		}
		else
			ft_add_var(cmd->argv[i], ms);
		i++;
	}
	return (0);
}
