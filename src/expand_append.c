/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:04:59 by jose-jim          #+#    #+#             */
/*   Updated: 2025/08/07 21:56:16 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_append_exit_code(char **result, t_ms *ms, int *i)
{
	char	*exit_code;

	exit_code = ft_itoa(g_signal);
	if (!exit_code)
		ft_exit_perror("malloc", 1, ms);
	*result = ft_strjoin_free(*result, exit_code);
	free(exit_code);
	if (!*result)
		ft_exit_perror("malloc", 1, ms);
	(*i)++;
	return (*i);
}

int	ft_append_var(t_ms *ms, char **result, char *str, int *i)
{
	int		j;
	char	*var_name;
	char	*var_value;

	j = ++(*i);
	if (str[*i] == '?')
		return (ft_append_exit_code(result, ms, i));
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_substr(str, j, *i - j);
	if (!var_name)
		return (-1);
	var_value = (char *) ft_kvl_get(ms->env, var_name);
	if (!var_value)
		var_value = "\0";
	free(var_name);
	if (var_value)
		*result = ft_strjoin_free(*result, var_value);
	if (!*result)
		return (-1);
	return (*i);
}

int	ft_append_plain_text(char **result, char *str, char quote, int *i)
{
	int		start;
	char	*new;

	start = *i;
	while (str[*i] && str[*i] != quote && !(str[*i] == '$' && quote == '"'))
		(*i)++;
	if (*i == start)
		return (0);
	new = ft_strjoin(*result, ft_substr(str, start, *i - start));
	free(*result);
	*result = new;
	if (!*result)
		return (-1);
	return (0);
}
