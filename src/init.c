/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:20:14 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/21 22:18:15 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_init_env_aux(char *value_str, char *env_str, t_ms *ms)
{
	size_t	key_size;
	char	*key;
	char	*value;
	t_kvl	*new_node;

	key_size = value_str - env_str;
	key = malloc(sizeof(char) * key_size);
	if (key == NULL)
		ft_exit_perror(NULL, 1, ms);
	ft_strlcpy(key, env_str, key_size);
	value = ft_strdup(value_str);
	if (value == NULL)
	{
		free(key);
		ft_exit_perror(NULL, 1, ms);
	}
	new_node = ft_kvl_new(key, value);
	free(key);
	if (new_node == NULL)
	{
		free(value);
		ft_exit_perror(NULL, 1, ms);
	}
	ft_kvl_add(&ms->env, new_node);
}

static void	ft_init_env(char *envp[], t_ms *ms)
{
	int		i;
	char	*env_str;
	char	*equal_sign;

	i = 0;
	env_str = envp[i];
	while (env_str != NULL)
	{
		equal_sign = ft_strchr(env_str, '=');
		if (equal_sign != NULL)
			ft_init_env_aux(equal_sign + 1, env_str, ms);
		i++;
		env_str = envp[i];
	}
}

void	ft_init(char *envp[], t_ms *ms)
{
	ft_signals_ignore();
	g_signal = 0;
	ft_memset(ms, 0, sizeof(t_ms));
	ft_init_env(envp, ms);
	//ft_print_env(ms);//Para debug
	//printf("Value de PATH: %s\n", (char *) ft_kvl_get(ms->env, "PATH"));
	ms->lines_count = 1;
	ms->heredoc[0] = -1;
	ms->heredoc[1] = -1;
}

/* Initializes ms->original_termios with the original terminal configuration
to be able to restore it. */
void	ft_init_termios(t_ms *ms)
{
	struct termios	original_termios;

	if (tcgetattr(STDIN_FILENO, &original_termios) == -1)
	{
		ms->termios_ok = 0;
		return ;
	}
	ms->termios_ok = 1;
	ms->orig_termios = original_termios;
	ft_setup_terminal(ms);
}
