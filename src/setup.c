/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:48:36 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/21 22:23:46 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Modifies the terminal configuration.
//TODO Comprobar si hay que hacerlo después de ejecutar programas o mantener cambios.
void	ft_setup_terminal(t_ms *ms)
{
	struct termios	term;

	if (ms->termios_ok == 0)
		return ;
	term = ms->orig_termios;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

//Restores the original terminal configuration.
//TODO Comprobar si hay que hacerlo antes de ejecutar programas.
void	ft_restore_terminal(t_ms *ms)
{
	if (ms->termios_ok == 0)
		return ;
	tcsetattr(STDIN_FILENO, TCSANOW, &ms->orig_termios);
}
