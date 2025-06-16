/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:39:13 by jose-jim          #+#    #+#             */
/*   Updated: 2024/11/21 15:21:38 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
	{
		i++;
	}
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

int	ft_strrncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	i = 0;
	if (n == 0)
		return (0);
	s1_len = ft_strlen(s1) -1;
	s2_len = ft_strlen(s2) - 1;
	while (s1[s1_len] == s2[s2_len] && i < n - 1)
	{
		i++;
		s1_len--;
		s2_len--;
	}
	return ((unsigned char) s1[s1_len] - (unsigned char) s2[s2_len]);
}
