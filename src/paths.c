/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:57:59 by jose-jim          #+#    #+#             */
/*   Updated: 2025/08/07 22:09:24 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_get_env_path(t_kvl *env)
{
	char	*env_path;
	char	**paths;

	env_path = ft_kvl_get(env, "PATH");
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*ft_strjoin_path(const char *path, const char *cmd)
{
	char	*full_path;
	size_t	path_len;
	size_t	cmd_len;

	if (!path || !cmd)
		return (NULL);
	path_len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	full_path = malloc(path_len + cmd_len + 2);
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, path, path_len + 1);
	if (path[path_len - 1] != '/')
		full_path[path_len++] = '/';
	ft_strlcpy(full_path + path_len, cmd, cmd_len + 1);
	return (full_path);
}

char	*ft_set_path(char *cmd, t_kvl *env)
{
	char	*path;
	char	**paths;
	size_t	i;

	if (!cmd || ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = ft_get_env_path(env);
	if (!paths)
		return (NULL);
	i = 0;
	path = NULL;
	while (paths[i])
	{
		path = ft_strjoin_path(paths[i], cmd);
		if (!path)
			break ;
		if (access(path, X_OK) == 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}
	ft_free_str_array(paths);
	return (path);
}

void	ft_resolve_paths(t_list *cmd_list, t_ms *ms)
{
	t_cmd	*cmd;

	while (cmd_list)
	{
		cmd = (t_cmd *)cmd_list->content;
		cmd_list = cmd_list->next;
		if (!ft_strcmp(cmd->argv[0], "cd")
			|| !ft_strcmp(cmd->argv[0], "echo")
			|| !ft_strcmp(cmd->argv[0], "pwd")
			|| !ft_strcmp(cmd->argv[0], "exit")
			|| !ft_strcmp(cmd->argv[0], "export")
			|| !ft_strcmp(cmd->argv[0], "unset")
			|| !ft_strcmp(cmd->argv[0], "env"))
			cmd->path = NULL;
		else
		{
			cmd->path = ft_set_path(cmd->argv[0], ms->env);
			if (!cmd->path)
				ft_error(cmd->argv[0], NULL, "command not found", 127);
		}
	}
}
