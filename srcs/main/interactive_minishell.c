/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_minishell.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:56:12 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/13 13:04:23 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	start_interactive_minishell(t_bash *bash, int debug)
{
	int	exit_status;

	set_signal_action();
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
		if (lexing(bash, bash->sequence) == RETURN_SUCCESS)
		{
			exit_status = parsing(bash);
			if (exit_status == PARSING_OK)
			{
				if (debug)
					test_print_instruction(bash->instruction);
				exec(bash->instruction, bash, bash->envp);
			}
			bash->exit_code = exit_status;
		}
		clear_instruction(&(bash)->instruction);
		free(bash->sequence);
		bash->sequence = NULL;
	}
	rl_clear_history();
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
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
