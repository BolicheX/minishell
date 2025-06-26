/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 22:46:12 by jose-jim          #+#    #+#             */
/*   Updated: 2025/06/26 18:30:19 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char *get_env_value(char *var_name, char **envp)
// {
// 	char *var = "Hola";
// 	(void)var_name;
// 	(void)envp;
// 	return (var);
// }

int ft_append_var(t_ms *ms, char **result, char *str, int *i)
{
	int j;
	char *var_name;
	char *var_value;
	char *tmp;

	j = ++(*i);
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_substr(str, j, *i - j);
	if (!var_name)
		return (ft_perror("malloc"), -1);
	//var_value = get_env_value(var_name, ms->envp);
	//var_value = "Hola";
	var_value = (char *) ft_kvl_get(ms->env, var_name);//Cuidado con las mayúsculas
	free(var_name);
	tmp = *result;
	*result = ft_strjoin(*result, var_value);
	free(tmp);
	if (!*result)
		return (ft_perror("malloc"), -1);
	return (*i);
}

int ft_append_plain_text(char **result, char *str, int *i)
{
	int start;
	char *new;

	start = *i;
	while (str[*i] && str[*i] != '$' && str[*i] != '\'' && str[*i] != '"')
		(*i)++;
	if (*i == start)
		return (0);
	new = ft_strjoin(*result, ft_substr(str, start, *i - start));
	free(*result);
	*result = new;
	if (!*result)
		return (ft_perror("malloc"), -1);
	return (0);
}

int ft_closed_quotes(const char *str, int i, char *quote)
{
	const char *closing;

	*quote = str[i];
	closing = ft_strchr(str + i + 1, *quote);
	if (closing)
		return (1);
	*quote = '\0';
	return (0);
}

int ft_handle_quotes(char *str, int *i, char *quote)
{
	if (!*quote && (str[*i] == '\'' || str[*i] == '"') && ft_closed_quotes(str, *i, quote))
	{
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

char *ft_replace_var(char *str, t_ms *ms)
{
	char *result;;
	int i;
	char quote;

	result = ft_strdup("");
	if (!result)
		return (ft_perror("malloc"), NULL);
	i = 0;
	quote = '\0';
	while (str[i])
	{
		if (ft_handle_quotes(str, &i, &quote))
			continue;
		if (quote != '\'' && str[i] == '$' && str[i + 1] &&
			(ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
		{
			if (ft_append_var(ms, &result, str, &i) == -1)
				return (free(result), NULL);
		}
		else if (ft_append_plain_text(&result, str, &i) == -1)
			return (free(result), NULL);
	}
	free(str);
	return (result);
}

int ft_has_unclosed_quotes(const char *str)
{
	char quote = '\0';
	int i = 0;
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

char *ft_check_expand(char **value, t_ms *ms)
{
	char *expanded_value = NULL;

	if (!*value)
		return (NULL);
	if (ft_has_unclosed_quotes(*value))
		return (ft_perror("minishell: syntax error: unclosed quotes"), NULL);
	if (ft_strchr(*value, '$') || ft_strchr(*value, '\'') || ft_strchr(*value, '\"'))
	{
		expanded_value = ft_replace_var(*value, ms);
		if (!expanded_value)
			return (NULL);
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
			if (!ft_check_expand(&token->value, ms))
				return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}
