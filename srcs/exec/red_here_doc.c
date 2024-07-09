/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:19:30 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/09 12:28:43 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	setup_here_doc(t_instruction *inst, t_token *current_red)
{
	char	*limiter;
	pid_t	reader;
	char	*line;

	limiter = current_red->option;
	if (inst_have_input_red(current_red->next) != 0)
		return (display_here_doc(limiter, inst));
	if (pipe(inst->fd_heredoc) == -1)
	{
		print_red_error("pipe here_doc()", current_red);
		return (-1);
	}
	reader = fork();
	if (reader == 0)
	{
		reset_fd_stdin_and_stdout(inst);
		close(inst->fd_heredoc[0]);
		while (1)
		{
			line = here_doc_readline(limiter);
			write(inst->fd_heredoc[1], line, strlen(line));
			write(inst->fd_heredoc[1], "\n", 1);
			free(line);
		}
	}
	else
	{
		close(inst->fd_heredoc[1]);
		dup2(inst->fd_heredoc[0], STDIN_FILENO);
		waitpid(reader, NULL, 0);
	}
	return (0);
}

int	display_here_doc(char *limiter, t_instruction *inst)
{
	pid_t	reader;
	char	*line;

	reader = fork();
	if (reader == 0)
	{
		reset_fd_stdin_and_stdout(inst);
		while (1)
		{
			line = here_doc_readline(limiter);
			free(line);
		}
	}
	else
		waitpid(reader, NULL, 0);
	return (0);
}

char	*here_doc_readline(char *limiter)
{
	char	*line;

	line = readline("> ");
	if (!line)
		exit(EXIT_SUCCESS);
	if (ft_my_strcmp(line, limiter) == 0)
	{
		free(line);
		exit(EXIT_SUCCESS);
	}
	return (line);
}
