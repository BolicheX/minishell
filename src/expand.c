/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 22:46:12 by jose-jim          #+#    #+#             */
/*   Updated: 2025/08/05 17:52:12 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_append_exit_code(char **result, t_ms *ms, int *i)
{
	char *exit_code;

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

int	ft_closed_quotes(const char *str, int i, char *quote)
{
	const char	*closing;

	*quote = str[i];
	closing = ft_strchr(str + i + 1, *quote);
	if (closing)
		return (1);
	*quote = '\0';
	return (0);
}

int	ft_handle_quotes(char *str, int *i, char *quote)
{
	if (!*quote && (str[*i] == '\'' || str[*i] == '"'))
	{
		quote[0] = str[*i];
		(*i)++;
		return (1);
	}
	if (*quote && str[*i] == *quote)
	{
		*quote = '\0';
		(*i)++;
		return (1);
	}
	return (0);
}

char	*ft_replace_var(char *s, t_ms *ms)
{
	char	*result;;
	int		i;
	char	quote;

	result = ft_strdup("");
	if (!result)
		ft_exit_perror("malloc", 1, ms);
	i = 0;
	quote = '\0';
	while (s[i])
	{
		if (ft_handle_quotes(s, &i, &quote))
			continue;
		if (quote != '\'' && s[i] == '$' && s[i + 1] &&
			(ft_isalpha(s[i + 1]) || s[i + 1] == '_' || s[i + 1] == '?'))
		{
			if (ft_append_var(ms, &result, s, &i) == -1)
				return (free(result), ft_exit_perror("malloc", 1, ms), NULL);
		}
		else if (ft_append_plain_text(&result, s, quote, &i) == -1)
			return (free(result), ft_exit_perror("malloc", 1, ms), NULL);
	}
	free(s);
	return (result);
}

int	ft_has_unclosed_quotes(const char *str)
{
	char	quote;
	int		i;

	quote = '\0';
	i = 0;
	while (str && str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = '\0';
		i++;
	}
	if (quote != '\0')
		return (1);
	return (0);
}

char	*ft_check_expand(char **value, t_ms *ms)
{
	char	*expanded_value;

	expanded_value = NULL;
	if (!*value)
		return (NULL);
	if (ft_has_unclosed_quotes(*value))
		return (ft_error("minishell", NULL, "unclosed quotes", 1), NULL);
	if (ft_strchr(*value, '$')
		|| ft_strchr(*value, '\'') || ft_strchr(*value, '\"'))
	{
		expanded_value = ft_replace_var(*value, ms);
		*value = expanded_value;
	}
	return (*value);
}

int ft_expand(t_list *tokens, t_ms *ms)
{
	t_token	*token;

	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->type == T_WORD)
		{
			if(!(ft_check_expand(&token->value, ms)) || !token->value)
			{
				ft_lstclear(&tokens, ft_del_token);
				return (-1);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}
