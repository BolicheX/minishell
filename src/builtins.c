/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:54:09 by jose-jim          #+#    #+#             */
/*   Updated: 2025/07/18 18:37:21 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_cmd *cmd)
{
	char	**argv;
	int		newline;
	int		i;

	argv = cmd->argv;
	i = 1;
	newline = 1;
	while (argv[i] && !ft_strncmp(argv[i], "-n", 2)
		&& ft_countchar(argv[i], 'n') == (int)(ft_strlen(argv[i]) - 1))
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], cmd->out);
		if (argv[i + 1])
			ft_putchar_fd(' ', cmd->out);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', cmd->out);
	return (0);
}

int	ft_pwd(t_cmd *cmd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		ft_error("pwd", NULL, NULL, 1);
	ft_putendl_fd(cwd, cmd->out);
	free(cwd);
	return (0);
}

int	ft_cd(t_cmd *cmd, t_ms *ms)
{
	char	*path;

	if (!cmd->argv[1])
	{
		path = ft_kvl_get(ms->env, "HOME");
		if (!path)
		{
			ft_error("cd", NULL, "HOME not set", 1);
			return (1);
		}
	}
	else
		path = cmd->argv[1];
	if (chdir(path) != 0)
	{
		ft_error("cd", path, NULL, 1);
		return (1);
	}
	return (0);
}

int	ft_env(t_cmd *cmd, t_ms *ms)
{
	t_kvl	*env;
	int		out_fd;

	env = ms->env;
	out_fd = cmd->out;
	while (env)
	{
		if (env->key && env->value)
		{
			ft_putstr_fd(env->key, out_fd);
			ft_putchar_fd('=', out_fd);
			ft_putendl_fd(env->value, out_fd);
		}
		env = env->next;
	}
	return (0);
}

