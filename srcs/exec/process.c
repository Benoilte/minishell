/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:51:22 by tmartin2          #+#    #+#             */
/*   Updated: 2024/07/05 09:05:14 by bebrandt         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/exec.h"

void parent_process(t_instruction *instruction)
{
    if (instruction->prev != NULL)
        close(instruction->prev->fd[0]);
    if (instruction->next != NULL)
        close(instruction->fd[1]);
}
void child_process(t_instruction *instruction, t_bash *bash, char **envp)
{
		ft_putstr_fd(instruction->cmd->data, STDERR_FILENO);
		ft_putstr_fd(": fd[0]: ", STDERR_FILENO);
		ft_putnbr_fd(instruction->fd[0], STDERR_FILENO);
		ft_putstr_fd(" fd[1] ", STDERR_FILENO);
		ft_putnbr_fd(instruction->fd[1], STDERR_FILENO);
		ft_putendl_fd("", STDERR_FILENO);
    if (instruction->prev != NULL)
    {
		ft_putstr_fd(instruction->cmd->data, STDERR_FILENO);
		ft_putstr_fd(": stdin: ", STDERR_FILENO);
		ft_putnbr_fd(STDIN_FILENO, STDERR_FILENO);
		ft_putstr_fd(" instruction->prev->fd[0] ", STDERR_FILENO);
		ft_putnbr_fd(instruction->prev->fd[0], STDERR_FILENO);
		ft_putendl_fd("", STDERR_FILENO);
        if (dup2(instruction->prev->fd[0], STDIN_FILENO) < 0)
		{
			print_cmd_error("dup2_stdin", instruction->cmd->data);
			clear_bash_and_exit(&bash, EXIT_FAILURE);
		}
        if (close(instruction->prev->fd[0]) < 0)
		{
			print_cmd_error("close", instruction->cmd->data);
			clear_bash_and_exit(&bash, EXIT_FAILURE);
		}
    }
    if (instruction->next != NULL)
    {
		ft_putstr_fd(instruction->cmd->data, STDERR_FILENO);
		ft_putstr_fd(": stdout: ", STDERR_FILENO);
		ft_putnbr_fd(STDOUT_FILENO, STDERR_FILENO);
		ft_putstr_fd(" instruction->fd[1] ", STDERR_FILENO);
		ft_putnbr_fd(instruction->fd[1], STDERR_FILENO);
		ft_putendl_fd("", STDERR_FILENO);
        if (dup2(instruction->fd[1], STDOUT_FILENO) < 0)
		{
			print_cmd_error("dup2_stdout", instruction->cmd->data);
			clear_bash_and_exit(&bash, EXIT_FAILURE);
		}
        if (close(instruction->fd[1]) < 0)
		{
			print_cmd_error("close", instruction->cmd->data);
			clear_bash_and_exit(&bash, EXIT_FAILURE);
		}
    }
    if (instruction->fd[0] != -1)
        close(instruction->fd[0]);
    if (instruction->fd[1] != -1)
        close(instruction->fd[1]);
    // while (instruction->red != NULL && ft_strcmp(instruction->cmd->data, "exit") != 0)
    // {
    //     if (sort_red(instruction, bash) < 0)
	// 		clear_bash_and_exit(&bash, EXIT_FAILURE);
    //     instruction->red = instruction->red->next;
    // }
	// ft_putstr_fd(instruction->cmd->data, STDERR_FILENO);
	// ft_putstr_fd(": stdin: ", STDERR_FILENO);
	// ft_putnbr_fd(STDIN_FILENO, STDERR_FILENO);
	// ft_putstr_fd(" stdout: ", STDERR_FILENO);
	// ft_putnbr_fd(STDOUT_FILENO, STDERR_FILENO);
	// ft_putendl_fd("", STDERR_FILENO);
	if (sort_red(instruction, bash) < 0)
		clear_bash_and_exit(&bash, EXIT_FAILURE);
    if (instruction->cmd != NULL || instruction->prev != NULL || ft_strcmp(instruction->cmd->data, "exit") == 0)
        sort_cmd_builtin(instruction, bash, envp);
}

int	wait_child_process(t_instruction *instruction)
{
	t_instruction	*current_inst;

	current_inst = instruction;
	while (current_inst != NULL)
	{
		if (waitpid(current_inst->pid, &current_inst->exit_status, 0) == -1)
			return (-1);
		current_inst = current_inst->next;
	}
	return (0);
}
