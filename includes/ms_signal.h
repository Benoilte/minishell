/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:25:55 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/18 19:31:29 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SIGNAL_H
# define MS_SIGNAL_H

# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>

# ifndef STDIN_FILENO
#  define STDIN_FILENO 0
# endif

extern int	g_signal_code;

enum
{
	UNSET,
	RESET
};

enum
{
	PARENT,
	CHILD,
	READLINE,
	DEFAULT,
	IGNORE
};

// signal.c

void	set_terminal(int config);
void	set_sig_int(int process);
void	set_sig_quit(int process);
void	parent_signal_handler(int signum);

#endif
