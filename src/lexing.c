/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:05:11 by jose-jim          #+#    #+#             */
/*   Updated: 2025/06/22 22:45:51 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static int	get_operator_precedence(char c)
{
	if (c == '|')
		return (1);
	if (c == '<' || c == '>')
		return (2);
	return (0);
} */

static int	skip_quotes(const char *line, int i)
{
	char quote = line[i];
	i++;
	while (line[i] && line[i] != quote)
		i++;
	if (line[i] == quote)
		i++;
	return (i);
}

static int	lex_operator(const char *line, int i, t_token **tokens)
{
	char	op;
	int		len;
	char	*str;
	t_token	*tok;

	op = line[i];
	len = 1;
	if ((op == '<' || op == '>') && line[i + 1] == op)
		len = 2;
	str = ft_substr(line, i, len);
	if (op == '|')
		tok = ft_new_token(T_PIPE, str);
	else
		tok = ft_new_token(T_REDIR, str);
	ft_add_token(tokens, tok);
	free(str);
	return (i + len);
}

static int	lex_word(const char *line, int i, t_token **tokens)
{
	int		start;;
	char	*str;
	t_token	*tok;

	start = i;
	while (line[i] && line[i] != ' ' && !ft_strchr("|<>", line[i]))
	{
		if (line[i] == '\'' || line[i] == '"')
			i = skip_quotes(line, i);
		else
			i++;
	}
	str = ft_substr(line, start, i - start);
	tok = ft_new_token(T_WORD, str);
	ft_add_token(tokens, tok);
	free(str);
	return (i);
}

t_token	*ft_lexing(char *line)
{
	int i = 0;
	t_token *tokens = NULL;

	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (!line[i])
			break;
		if (ft_strchr("|<>", line[i]))
			i = lex_operator(line, i, &tokens);
		else
			i = lex_word(line, i, &tokens);
	}
	return (tokens);
}

int	ft_transform_cmd(char *cmd_line, t_ms *ms)
{
	t_token *tokens;

	tokens = ft_lexing(cmd_line);
	ft_expand(tokens, ms);
	ft_print_tokens(tokens);
	printf("%s\n", cmd_line);
	(void)ms;
	return(0);
}