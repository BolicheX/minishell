/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:02:24 by jescuder          #+#    #+#             */
/*   Updated: 2025/06/26 18:16:25 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Closes a fd in a secure way checking and setting a -1 value.
void	ft_close(int *fd)
{
	if (*fd == -1)
        return ;
	if (close(*fd) == -1)
        ft_perror("error");
    *fd = -1;
}

void	ft_free_str_array(char **array)
{
	size_t	i;

    if (array == NULL)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

//Closes every file descriptor in t_ms.
static void ft_close_all(t_ms *ms)
{
	(void) ms;
    //TODO Esperar a ver de qué manera y dónde se guardan los fd durante el parsing. Y entonces cerrarlos.
    //Posiblemente lo mejor sea guardarlos en una lista enlazada durante el parseo y para cerrarlos no haya que tocar sus copias en t_cmd(campos in y out).
    //Otra opción es guardarlos sólo en los campos in y out de los t_cmd teniendo cuidado durante el parseo de que, en los casos en que el programa deba cerrarse
    //por algún error, no se quede ninguno abierto y sin asignar a un t_cmd, porque entonces esta función no lo cerraría.
}

//Frees all heap memory in t_ms.
static void ft_free_all(t_ms *ms)
{
	//ft_free_str_array(ms->envp);
	//ft_free_str_array(ms->envp_paths);
	ft_kvl_clear(&ms->env, free);
	//TODO Los demás campos de ms que estén en heap memory.
}

//Closes every file descriptor and frees all heap memory in t_ms.
void    ft_clean_all(t_ms *ms)
{
    ft_close_all(ms);
    ft_free_all(ms);
}
