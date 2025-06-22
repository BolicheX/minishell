/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:40:05 by jose-jim          #+#    #+#             */
/*   Updated: 2025/06/22 22:13:53 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	token->next = NULL;
	return (token);
}

void	ft_add_token(t_token **list, t_token *new)
{
	t_token	*temp;

	if (!list || !new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	ft_print_tokens(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == T_WORD)
			printf("[WORD]  [%s]\n", tokens->value);
		else if (tokens->type == T_REDIR)
			printf("[REDIR] [%s]\n", tokens->value);
		else if (tokens->type == T_PIPE)
			printf("[PIPE]  [%s]\n", tokens->value);
		tokens = tokens->next;
	}
}
