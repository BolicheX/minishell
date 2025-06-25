/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:41:43 by jescuder          #+#    #+#             */
/*   Updated: 2025/06/25 12:34:56 by jose-jim         ###   ########.fr       */
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
				ft_exit_error(NULL, 1, ms);
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

//There are arguments or STDIN_FILENO was redirected to a file or a pipe,
//so we don't execute in interactive mode.
void    ft_non_interactive_execution(int argc, char *argv[], t_ms *ms)
{
    (void) argc;
    (void) argv;
    ft_exit_clean(1, ms);
}

int main(int argc, char *argv[], char *envp[])
{
    t_ms    ms;
    char    *cmd_line;

    ft_init(envp, &ms);
    if (argc != 1 || isatty(STDIN_FILENO) == 0)
        ft_non_interactive_execution(argc, argv, &ms);
    while (1)
    {
        //TODO Probablemente haya que actualizar envp en cada iteración, por si cambia. Probablemente con getenv.
        cmd_line = readline("$ ");
        if (cmd_line == NULL)
        {
            ft_putendl_fd("exit", STDERR_FILENO);
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
