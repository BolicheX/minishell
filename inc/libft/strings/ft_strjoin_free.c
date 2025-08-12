/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:32:51 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/12 00:41:24 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *str1, char *str2)
{
	char	*str_join;

	str_join = ft_strjoin(str1, str2);
	if (!str_join)
		return (NULL);
	free(str1);
	return (str_join);
}

char	*ft_strjoin_free2(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (!res)
		return (NULL);
	free(s1);
	free(s2);
	return (res);
}

