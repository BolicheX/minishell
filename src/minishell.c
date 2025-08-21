/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:41:43 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/22 00:10:56 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Interprets a command line by lexing, expanding, parsing and executing.
//If it's a heredoc command, ft_heredoc manages the following lines, asks for
//more if necessary and sets the lines after the limiter to be traversed here
//after the execution of the heredoc command.
static int	ft_interpret_input_line(char *cmd_line, int i, t_ms *ms)
{
	int	is_heredoc;

	is_heredoc = 0;
	if (ft_lexing(cmd_line, &ms->tokens, ms))
		return (0);
	if (ft_heredoc_init(ms->tokens, ms))
		return (0);
	if (ms->limiter != NULL)
	{
		is_heredoc = 1;
		if (ft_heredoc(i, ms) == 0)
			return (1);
	}
	else
		ft_add_history(cmd_line, ms);
	if (ft_expand(ms) == -1)
		return (is_heredoc);
	ft_lstclear(&ms->cmds, ft_clean_cmd);
	ft_parse(ms);
	if (!ms->cmds)
		return (is_heredoc);
	if (ft_resolve_paths(&ms->cmds, ms))
		return (is_heredoc);
	ft_execute(ms->cmds, ms);
	return (is_heredoc);
}

//Traverses input lines to interpret them. It returns if a heredoc is
//found, because the following input lines are managed internally
//since more can be added in the heredoc input.
static void	ft_traverse_input(t_ms *ms)
{
	char	**input_lines;
	int		i;
	int		is_heredoc;

	input_lines = ms->input_lines;
	if (input_lines == NULL)
		return ;
	i = 0;
	while (input_lines[i] != NULL)
	{
		if (*input_lines[i] != '\0')
		{
			is_heredoc = ft_interpret_input_line(input_lines[i], i, ms);
			if (is_heredoc == 1)
			{
				ft_traverse_input(ms);
				return ;
			}
		}
		ms->lines_count++;
		i++;
	}
}

static void	ft_non_interactive_mode(char *input, int do_free, t_ms *ms)
{
	char	**input_lines;

	input_lines = ft_split_empty(input, '\n');
	if (do_free)
		free(input);
	if (input_lines == NULL)
		ft_exit_perror(NULL, 1, ms);
	ms->input_lines = input_lines;
	ft_traverse_input(ms);
}

static void	ft_interactive_mode(t_ms *ms)
{
	char	*prompt;
	char	*input;
	char	**input_lines;

	prompt = "\001\033[1;34m\002minishell\001\033[0m\002$ ";
	while (1)
	{
		ft_signals_interactive();
		input = readline(prompt);
		ft_check_signal(ms);
		if (input == NULL)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			ft_exit_clean(ms->exit_code, ms);
		}
		input_lines = ft_split_empty(input, '\n');
		free(input);
		if (input_lines == NULL)
			ft_exit_perror(NULL, 1, ms);
		ms->input_lines = input_lines;
		ft_traverse_input(ms);
		ft_free_str_array(ms->input_lines);
		ms->input_lines = NULL;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_ms	ms;
	char	*input;

	ft_init(envp, &ms);
	if (argc >= 3 && !ft_strcmp(argv[1], "-c"))
	{
		ms.is_interactive = 0;
		ft_non_interactive_mode(argv[2], 0, &ms);
	}
	else if (isatty(STDIN_FILENO) == 0)
	{
		input = ft_fd_to_str(STDIN_FILENO);
		if (input == NULL)
			ft_exit_perror(NULL, 1, &ms);
		ms.is_interactive = 0;
		ft_non_interactive_mode(input, 1, &ms);
	}
	else
	{
		ms.is_interactive = 1;
		ft_interactive_mode(&ms);
	}
	ft_clean_all(&ms);
	return (ms.exit_code);
}
