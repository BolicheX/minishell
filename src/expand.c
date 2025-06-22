/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 22:46:12 by jose-jim          #+#    #+#             */
/*   Updated: 2025/06/23 00:07:05 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_append_var(t_ms *ms, char **result, char *str, int i)
{
	int	j;
	char	*var_name;
	char	*var_value;
	char	*tmp;

	j = i;
	i++;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = ft_substr(str, j, i - j);
	var_value = get_env_value(var_name, ms->envp);
	tmp = *result;
	*result = ft_strjoin(*result, var_value);
	free(tmp);
	free(var_name);
	return (i);
}

void	ft_append_char(char **result, char *str, int *i)
{
	char	*c;
	char	*tmp;

	c = ft_substr(str, *i, 1);
	tmp = *result;
	*result = ft_strjoin(*result, c);
	free(c);
	free(tmp);
	(*i)++;
}

char	*ft_expand(char *str, t_ms *ms)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
			ft_append_var(ms, &result, str, &i);
		else
			ft_append_char(&result, str, &i);
	}
	return (result);
}

int	ft_expand_clean(t_token *tokens, t_ms *ms)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if (tokens->type = T_WORD &&
			(*tokens->value == "\'" || *tokens->value == "\""))
		{
			if (*tokens->value == "\"")
				tokens->value = ft_expand(tokens->value, ms);
			ft_clean(&tokens->value);
		}
		tokens = tokens->next;
	}
	return (0);
}
