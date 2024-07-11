/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_here_doc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:54:33 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/11 00:36:29 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	handle_here_doc_process(pid_t reader, t_instruction *inst,
		t_token *red, t_bash *bash)
{
	if (reader == -1)
		return (-1);
	else if (reader == 0)
		child_here_doc_process(inst, red, bash);
	else
		return (parent_here_doc_process(reader, inst, red));
	return (0);
}

void	child_here_doc_process(t_instruction *inst, t_token *red,
			t_bash *bash)
{
	char	*line;

	set_sig_int(DEFAULT);
	reset_fd_stdin_and_stdout(inst);
	close_and_reset_pipe_fd(inst, inst->fd);
	close_and_reset_pipe_fd(inst, inst->fd + 1);
	if (close(inst->fd_heredoc[0]) < 0)
		print_red_error(" close child_here_doc_process()", red);
	while (1)
	{
		line = here_doc_readline(red->option, inst, red, bash);
		write(inst->fd_heredoc[1], line, strlen(line));
		write(inst->fd_heredoc[1], "\n", 1);
		free(line);
	}
}

int	parent_here_doc_process(pid_t reader, t_instruction *inst,
			t_token *red)
{
	if (close(inst->fd_heredoc[1]) < 0)
	{
		print_red_error("close parent_here_doc_process()", red);
		return (-1);
	}
	if (dup2(inst->fd_heredoc[0], STDIN_FILENO) < 0)
	{
		print_red_error("dup2 parent_here_doc_process()", red);
		return (-1);
	}
	if (close(inst->fd_heredoc[0]) < 0)
	{
		print_red_error("close parent_here_doc_process()", red);
		return (-1);
	}
	if (waitpid(reader, &inst->exit_status, 0) < 0)
	{
		print_red_error("waitpid parent_here_doc_process()", red);
		return (-1);
	}
	return (check_child_exit_status(inst));
}

int	check_child_exit_status(t_instruction *inst)
{
	if (inst->exit_status == SIGINT)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		inst->exit_status = 130;
		return (-1);
	}
	return (0);
}
