/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_desriptors_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 07:45:32 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/11 09:37:45 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	close_and_reset_pipes(t_instruction *curent_inst)
{
	int	close_fd_0;
	int	close_fd_1;

	close_fd_0 = 0;
	close_fd_1 = 0;
	if (close_and_reset_pipe_fd(curent_inst, curent_inst->fd) < 0)
		close_fd_0 = -1;
	if (close_and_reset_pipe_fd(curent_inst, curent_inst->fd + 1) < 0)
		close_fd_1 = -1;
	if ((close_fd_0 < 0) || (close_fd_1 < 0))
		return (-1);
	return (0);
}

int	close_and_reset_pipe_fd(t_instruction *curent_inst, int *fd)
{
	if (*fd >= 0)
	{
		if (close(*fd) < 0)
		{
			print_cmd_error("close", curent_inst->cmd);
			return (-1);
		}
		*fd = -1;
	}
	return (0);
}

void	close_unused_pipe_fd(t_instruction *current_inst, t_bash *bash)
{
	if (current_inst->fd[0] != -1)
	{
		if (close_and_reset_pipe_fd(current_inst, current_inst->fd) < 0)
			clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
	if (current_inst->fd[1] != -1)
	{
		if (close_and_reset_pipe_fd(current_inst, current_inst->fd + 1) < 0)
			clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
}

int	close_here_doc_fd(int fd, char *sender, t_token *red)
{
	if (fd != -1 && close(fd) < 0)
	{
		print_red_error(sender, red);
		return (-1);
	}
	return (0);
}
