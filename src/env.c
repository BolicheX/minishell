/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 21:28:28 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/21 21:52:40 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_join_env(char *key, char *value)
{
	char	*str;
	int		str_size;

	str_size = ft_strlen(key) + ft_strlen(value) + 2;
	str = malloc (sizeof(char) * str_size);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, key, str_size);
	ft_strlcat(str, "=", str_size);
	ft_strlcat(str, value, str_size);
	return (str);
}

//Gets an array that represents the environment variables stored in ms->env.
char	**ft_env_to_array(t_ms *ms)
{
	t_kvl	*env;
	int		array_len;
	char	**array;
	int		i;

	env = ms->env;
	array_len = ft_kvl_size(env);
	array = malloc (sizeof(char *) * (array_len + 1));
	if (array == NULL)
		ft_exit_perror(NULL, 1, ms);
	i = 0;
	while (i < array_len)
	{
		array[i] = ft_join_env(env->key, env->value);
		if (array[i] == NULL)
		{
			ft_free_str_array(array);
			ft_exit_perror(NULL, 1, ms);
		}
		env = env->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
