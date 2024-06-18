/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:32:12 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/18 17:46:51 by bebrandt         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/exec.h"

void	set_terminal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag ^= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	set_sig_int(int process)
{
	struct sigaction	new_action;

	if (process == PARENT)
	{
		new_action.sa_handler = &parent_signal_handler;
		sigemptyset(&new_action.sa_mask);
		new_action.sa_flags = 0;
		sigaction(SIGINT, &new_action, NULL);
	}
	else if (process == CHILD)
	{
		new_action.sa_handler = SIG_DFL;
		sigemptyset(&new_action.sa_mask);
		new_action.sa_flags = 0;
		sigaction(SIGINT, &new_action, NULL);
	}
}

void	set_sig_quit(int process)
{
	if (process == PARENT)
		signal(SIGQUIT, SIG_IGN);
	else if (process == CHILD)
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

void	child_signal_handler(int signum)
{
	(void)signum;
}
