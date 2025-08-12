/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:05:11 by jose-jim          #+#    #+#             */
/*   Updated: 2025/08/12 00:24:28 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_quotes(const char *line, int i)
{
	char	quote;

	quote = line[i];
	i++;
	while (line[i] && line[i] != quote)
		i++;
	if (line[i] == quote)
		i++;
	return (i);
}

int	lex_operator(const char *line, int i, t_list **tokens)
{
	char	op;
	int		len;
	char	*str;

	op = line[i];
	len = 1;
	if ((op == '<' || op == '>') && line[i + 1] == op)
		len = 2;
	str = ft_substr(line, i, len);
	if (!str)
		return (i + len);
	if (op == '|')
		ft_add_token(tokens, T_PIPE, str);
	else
		ft_add_token(tokens, T_REDIR, str);
	free(str);
	return (i + len);
}

int	lex_word(const char *line, int i, t_list **tokens)
{
	int		start;
	char	*str;

	start = i;
	while (line[i] && line[i] != ' ' && !ft_strchr("|<>", line[i]))
	{
		if (line[i] == '\'' || line[i] == '"')
			i = skip_quotes(line, i);
		else
			i++;
	}
	str = ft_substr(line, start, i - start);
	if (str)
		ft_add_token(tokens, T_WORD, str);
	free(str);
	return (i);
}

int	ft_lexing_check(t_list *tokens)
{
	t_token	*tok;
	t_token	*next_tok;

	if (!tokens)
		return (1);
	tok = (t_token *)tokens->content;
	if (tok->type == T_PIPE)
		return (ft_syntax_error("|", 2));
	while (tokens->next)
	{
		tok = (t_token *)tokens->content;
		next_tok = (t_token *)tokens->next->content;
		if (tok->type == T_PIPE && next_tok->type == T_PIPE)
			return (ft_syntax_error("|", 2));
		if (tok->type == T_REDIR && next_tok->type != T_WORD)
			return (ft_syntax_error(next_tok->value, 2));
		tokens = tokens->next;
	}
	tok = (t_token *)tokens->content;
	if (tok->type == T_PIPE)
		return (ft_syntax_error("|", 2));
	return (0);
}

int	ft_lexing(char *line, t_list **tokens)
{
	int		i;

	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		if (ft_strchr("|<>", line[i]))
			i = lex_operator(line, i, tokens);
		else
			i = lex_word(line, i, tokens);
	}
	return (ft_lexing_check(*tokens));
}
