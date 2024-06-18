/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_minishell.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tommartinelli <tommartinelli@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:56:12 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/17 17:07:07 by tommartinel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	start_interactive_minishell(t_bash *bash, int debug)
{
	set_signal_action();
	while (1)
	{
		bash->sequence = readline("minishell> ");
		if (!bash->sequence)
		{
			ft_printf("exit\n");
			clear_bash_and_exit(&bash, EXIT_FAILURE);
		}
		if (ft_strlen(bash->sequence) > 0)
			add_history(bash->sequence);
		if (lexing(bash, bash->sequence) == RETURN_SUCCESS)
		{
			if (parsing(bash) == PARSING_OK)
			{
				if (debug)
					test_print_instruction(bash->instruction);
				exec(bash->instruction, bash, bash->envp);
			}
		}
		clear_instruction(&(bash)->instruction);
		free(bash->sequence);
		bash->sequence = NULL;
	}
	clear_history();// rl_clear_history pour mon mac
}

void	set_signal_action(void)
{
	struct sigaction	new_action;

	signal(SIGQUIT, SIG_IGN);
	new_action.sa_handler = &signal_handler;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = 0;
	sigaction(SIGINT, &new_action, NULL);
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
}
