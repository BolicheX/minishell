/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:54:09 by jose-jim          #+#    #+#             */
/*   Updated: 2025/07/17 16:02:28 by jose-jim         ###   ########.fr       */
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
		ft_perror("Error getting current working directory");
	ft_putendl_fd(cwd, cmd->out);
	free(cwd);
	return (0);
}

