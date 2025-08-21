/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 22:46:12 by jose-jim          #+#    #+#             */
/*   Updated: 2025/08/21 13:20:10 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*result;
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
			continue ;
		if (quote != '\'' && s[i] == '$' && s[i + 1]
			&& (ft_isalpha(s[i + 1]) || s[i + 1] == '_' || s[i + 1] == '?'))
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
	if (!*value)
		return (NULL);
	if (ft_has_unclosed_quotes(*value))
		return (ft_error(NULL, NULL, "unclosed quotes", ms), NULL);
	if (ft_strchr(*value, '$')
		|| ft_strchr(*value, '\'') || ft_strchr(*value, '\"'))
		*value = ft_replace_var(*value, ms);
	return (*value);
}

int	ft_expand(t_ms *ms)
{
	t_token	*token;
	t_list	*current;

	current = ms->tokens;
	while (current)
	{
		token = (t_token *)current->content;
		if (token->type == T_WORD)
		{
			if (!(ft_check_expand(&token->value, ms)) || !token->value)
			{
				ft_lstclear(&ms->tokens, ft_del_token);
				return (-1);
			}
		}
		current = current->next;
	}
	return (0);
}

/* int	ft_closed_quotes(const char *str, int i, char *quote)
{
	const char	*closing;

	*quote = str[i];
	closing = ft_strchr(str + i + 1, *quote);
	if (closing)
		return (1);
	*quote = '\0';
	return (0);
} */