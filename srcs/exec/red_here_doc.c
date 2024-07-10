/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:19:30 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/10 23:14:11 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	setup_here_doc(t_instruction *inst, t_token *red, t_bash *bash)
{
	pid_t	reader;

	if (inst_have_input_red(red->next) != 0)
		return (display_here_doc(red->option, inst, red, bash));
	if (pipe(inst->fd_heredoc) == -1)
	{
		print_red_error("pipe here_doc()", red);
		return (-1);
	}
	reader = fork();
	return (handle_here_doc_process(reader, inst, red, bash));
}

int	display_here_doc(char *limiter, t_instruction *inst, t_token *red,
		t_bash *bash)
{
	pid_t	reader;
	char	*line;

	reader = fork();
	if (reader == -1)
		return (-1);
	if (reader == 0)
	{
		reset_fd_stdin_and_stdout(inst);
		close_and_reset_pipe_fd(inst, inst->fd);
		close_and_reset_pipe_fd(inst, inst->fd + 1);
		while (1)
		{
			line = here_doc_readline(limiter, inst, red, bash);
			free(line);
		}
	}
	else
	{
		if (waitpid(reader, NULL, 0) < 0)
			return (-1);
	}
	return (0);
}

char	*here_doc_readline(char *limiter, t_instruction *inst, t_token *red,
			t_bash *bash)
{
	char	*line;

	line = readline("> ");
	if (!line)
	{
		ft_putchar_fd('\n', STDIN_FILENO);
		if (close_here_doc_fd(inst->fd_heredoc[1], "heredoc_readline()", red))
			clear_bash_and_exit(&bash, EXIT_FAILURE);
		clear_bash_and_exit(&bash, EXIT_SUCCESS);
	}
	if (ft_my_strcmp(line, limiter) == 0)
	{
		free(line);
		if (close_here_doc_fd(inst->fd_heredoc[1], "heredoc_readline()", red))
			clear_bash_and_exit(&bash, EXIT_FAILURE);
		clear_bash_and_exit(&bash, EXIT_SUCCESS);
	}
	return (line);
}
