/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:54:09 by jose-jim          #+#    #+#             */
/*   Updated: 2025/08/11 21:49:06 by jescuder         ###   ########.fr       */
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
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		ft_error("pwd", NULL, NULL, 1);
	ft_putendl_fd(cwd, STDOUT_FILENO);
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
	else if (cmd->argv[2])
	{
		ft_error("cd", NULL, "too many arguments", 1);
		return (1);
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

int	ft_env(t_ms *ms)
{
	t_kvl	*env;

	env = ms->env;
	while (env)
	{
		if (env->key && env->value)
		{
			ft_putstr_fd(env->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(env->value, STDOUT_FILENO);
		}
		env = env->next;
	}
	return (0);
}

int	ft_unset(t_cmd *cmd, t_ms *ms)
{
	char	**argv;
	int		i;

	argv = cmd->argv;
	i = 1;
	while (argv[i])
	{
		ft_kvl_remove(&ms->env, argv[i], free);
		i++;
	}
	return (0);
}
