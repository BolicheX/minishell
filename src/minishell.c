
#include "minishell.h"

static void ft_init(t_ms *ms, char *envp[])
{
    ft_memset(ms, 0, sizeof(t_ms));
    ms->envp = envp;
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
        cmd_line = readline("$ ");
        (void) cmd_line;
        //printf("%s\n", cmd_line);
        //ft_transform_cmd(cmd_line, &ms); //Lexing+Expanding+Parsing. Cámbiale el nombre a esta función a tu gusto.
        //ft_execute_cmd(&ms);
        ms.cmd_line_num++;
    }
    return (0);
}
