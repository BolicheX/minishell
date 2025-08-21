/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:04:59 by jose-jim          #+#    #+#             */
/*   Updated: 2025/08/21 12:39:24 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_append_exit_code(char **result, t_ms *ms, int *i)
{
	char	*exit_code;

	exit_code = ft_itoa(ms->exit_code);
	if (!exit_code)
		ft_exit_perror(NULL, 1, ms);
	*result = ft_strjoin_free(*result, exit_code);
	free(exit_code);
	if (!*result)
		ft_exit_perror(NULL, 1, ms);
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
	return (0);
}

int	ft_append_plain_text(char **result, char *str, char quote, int *i)
{
	int		start;

	start = *i;
	while (str[*i]
		&& ((quote == '\'' && str[*i] != quote)
			|| (quote == '"' && str[*i] != quote && str[*i] != '$')
			|| (quote == '\0' && str[*i] != '$'
				&& str[*i] != '\'' && str[*i] != '"')))
		(*i)++;
	if (*i == start)
	{
		*result = ft_strjoin_free2(*result, ft_substr(str, *i, 1));
		(*i)++;
	}
	else
		*result = ft_strjoin_free2(*result, ft_substr(str, start, *i - start));
	if (!*result)
		return (-1);
	return (0);
}
