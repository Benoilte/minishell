/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:32:12 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/18 19:34:50 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	set_terminal(int config)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (config == UNSET && (term.c_lflag & ECHOCTL))
		term.c_lflag ^= ECHOCTL;
	else if (config == RESET && ((term.c_lflag & ECHOCTL) == 0))
		term.c_lflag ^= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	set_sig_int(int process)
{
	struct sigaction	new_action;

	if (process == READLINE)
	{
		new_action.sa_handler = &parent_signal_handler;
		sigemptyset(&new_action.sa_mask);
		new_action.sa_flags = 0;
		sigaction(SIGINT, &new_action, NULL);
	}
	else if (process == DEFAULT)
	{
		new_action.sa_handler = SIG_DFL;
		sigemptyset(&new_action.sa_mask);
		new_action.sa_flags = 0;
		sigaction(SIGINT, &new_action, NULL);
	}
	else if (process == IGNORE)
		signal(SIGINT, SIG_IGN);
}

void	set_sig_quit(int process)
{
	if (process == IGNORE)
		signal(SIGQUIT, SIG_IGN);
	else if (process == DEFAULT)
		signal(SIGQUIT, SIG_DFL);
}

void	parent_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal_code = SIGINT;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
