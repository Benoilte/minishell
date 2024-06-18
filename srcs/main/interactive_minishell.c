/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_minishell.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:56:12 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/18 15:57:30 by bebrandt         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void	start_interactive_minishell(t_bash *bash, int debug)
{
	set_signal_action(PARENT);
	while (1)
	{
		bash->sequence = readline("minishell> ");
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
	rl_clear_history();
}
