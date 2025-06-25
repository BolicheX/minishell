/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:40:05 by jose-jim          #+#    #+#             */
/*   Updated: 2025/06/25 21:24:48 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add_token(t_list **tokens, t_token_type type, const char *value)
{
	t_token	*token;
	t_list	*node;

	token = malloc(sizeof(t_token));
	if (!token)
		return (0);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (0);
	}
	node = ft_lstnew(token);
	if (!node)
	{
		free(token->value);
		free(token);
		return (0);
	}
	ft_lstadd_back(tokens, node);
	return (1);
}

void	ft_del_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->value);
	free(token);
}
