/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_minishell.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:56:12 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/12 08:52:59 by bebrandt         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

int	g_signal_code;

void	start_interactive_minishell(t_bash *bash, int debug)
{
	g_signal_code = 0;
	if (debug)
		test_print_ms_env(bash->ms_env);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			set_terminal(UNSET);
		set_sig_int(READLINE);
		bash->sequence = readline("minishell> ");
		set_sig_int(IGNORE);
		if (!bash->sequence)
		{
			if (g_signal_code)
				bash->exit_code = 128 + g_signal_code;
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
}
