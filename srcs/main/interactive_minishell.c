/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_minishell.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tommartinelli <tommartinelli@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:56:12 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/19 14:39:44 by tommartinel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_signal_code = 0;

void	start_interactive_minishell(t_bash *bash, int debug)
{
	g_signal_code = 0;
	set_sig_quit(IGNORE);
	while (1)
	{
		set_terminal(UNSET);
		set_sig_int(READLINE);
		bash->sequence = readline("minishell> ");
		set_sig_int(IGNORE);
		if (!bash->sequence)
		{
			ft_printf("exit\n");
			clear_bash_and_exit(&bash, bash->exit_code);
		}
		if (ft_strlen(bash->sequence) > 0)
			add_history(bash->sequence);
		check_sequence_and_execution(bash, debug);
		clear_instruction(&(bash)->instruction);
		free(bash->sequence);
		bash->sequence = NULL;
	}
	clear_history();
}
