/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:37:32 by jose-jim          #+#    #+#             */
/*   Updated: 2025/07/20 20:45:05 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_kvl *ft_kvl_strclone(t_kvl *env)
{
	t_kvl	*clone;
	t_kvl	*node;
	char	*value_dup;

	clone = NULL;
	while (env)
	{
		value_dup = NULL;
		if (env->value)
		{
			value_dup = ft_strdup(env->value);
			if (!value_dup)
				return (ft_kvl_clear(&clone, free));
		}
		node = ft_kvl_new(env->key, value_dup);
		if (!node)
		{
			free(value_dup);
			return (ft_kvl_clear(&clone, free));
		}
		ft_kvl_add(&clone, node);
		env = env->next;
	}
	return (clone);
}

t_kvl *ft_kvl_alphasort(t_kvl *lst)
{
	t_kvl *sorted;
	t_kvl *curr;
	t_kvl *pos;

	sorted = NULL;
	while (lst)
	{
		curr = lst;
		lst = lst->next;
		if (!sorted || ft_strcmp(curr->key, sorted->key) < 0)
		{
			curr->next = sorted;
			sorted = curr;
		}
		else
		{
			pos = sorted;
			while (pos->next && ft_strcmp(curr->key, pos->next->key) > 0)
				pos = pos->next;
			curr->next = pos->next;
			pos->next = curr;
		}
	}
	return sorted;
}

static void	ft_export_print(t_kvl *sorted, int out_fd)
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
		ft_error("export", str, "memory allocation error", 1);
		return (1);
	}
	ft_kvl_set(&ms->env, key, value);
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
			ft_error("export", cmd->argv[i], "not a valid identifier", 1);
			i++;
			continue;
		}
		else
			ft_add_var(cmd->argv[i], ms);
		i++;
	}
	return (0);
}
