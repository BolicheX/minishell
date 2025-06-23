/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:41:43 by jescuder          #+#    #+#             */
/*   Updated: 2025/06/23 18:05:56 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void set_envp_paths(t_ms *ms)
{
    char    **envp;
	char	**envp_paths;
	size_t	i;

    envp = ms->envp;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			envp_paths = ft_split(envp[i] + 5, ':');
			if (envp_paths == NULL)
				ft_print_error(NULL, 1, ms);
			ms->envp_paths = envp_paths;
			return ;
		}
		i++;
	}
}

static void ft_init(char *envp[], t_ms *ms)
{
    ft_memset(ms, 0, sizeof(t_ms));
    ms->envp = envp;
    set_envp_paths(ms);
    ms->cmd_line_num = 1;//Contador de líneas necesario para cierto mensaje de error.
}

int main(int argc, char *argv[], char *envp[])
{
    t_ms    ms;
    char    *cmd_line;

    ft_init(&ms, envp);
    //Como es en modo interactivo, ver si hay que terminar con error si se introducen argumentos, o si sólo hay que ignorarlos.
    (void) argc;
    (void) argv;
    while (1)
    {
        //TODO Probablemente haya que actualizar envp en cada iteración, por si cambia. Probablemente con getenv.
        cmd_line = readline("$ ");
        if (cmd_line == NULL)
        {
            ft_putstr_fd("Signal received. Stop.\n", STDERR_FILENO);
            return (1);
        }
        //printf("%s\n", cmd_line);
        ft_transform_cmd(cmd_line, &ms); //Lexing+Expanding+Parsing. Cámbiale el nombre a esta función a tu gusto.
        //ft_execute_cmd(&ms);
        ms.cmd_line_num++;
        free(cmd_line);
    }
    return (0);
}
