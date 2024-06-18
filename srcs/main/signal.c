/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:32:12 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/18 15:14:04 by bebrandt         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/exec.h"

void	set_signal_action(int process)
{
	struct sigaction	new_action;

	if (process == PARENT)
	{
		signal(SIGQUIT, SIG_IGN);
		new_action.sa_handler = &parent_signal_handler;
		sigemptyset(&new_action.sa_mask);
		new_action.sa_flags = 0;
		sigaction(SIGINT, &new_action, NULL);
	}
	else if (process == CHILD)
	{
		signal(SIGQUIT, SIG_DFL);
		new_action.sa_handler = SIG_DFL;
		sigemptyset(&new_action.sa_mask);
		new_action.sa_flags = 0;
		sigaction(SIGINT, &new_action, NULL);
	}
}

void	parent_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
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
