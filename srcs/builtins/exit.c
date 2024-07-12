/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:24:31 by tommartinel       #+#    #+#             */
/*   Updated: 2024/07/12 16:32:21 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	count_arguments(t_token *cmd)
{
	int			arg_count;
	t_token		*arg;

	arg_count = 0;
	arg = cmd->next;
	while (arg != NULL)
	{
		arg_count++;
		arg = arg->next;
	}
	return (arg_count);
}

void	finalize_exit(t_instruction *instruction, t_bash *bash, int arg_count)
{
	reset_fd_stdin_and_stdout(instruction);
	if (arg_count == 1)
		bash->exit_code = ft_atoi(instruction->cmd->next->data);
	ft_putendl_fd("exit", STDOUT_FILENO);
	clear_bash_and_exit(&bash, bash->exit_code);
}

void	ft_exit(t_instruction *instruction, t_bash *bash)
{
	int			arg_count;

	if (instruction->cmd != NULL && instruction->cmd->data != NULL
		&& ft_my_strcmp(instruction->cmd->data, "exit") == 0)
	{
		arg_count = count_arguments(instruction->cmd);
		if (too_many_arg(arg_count, instruction))
			return ;
		if (arg_is_not_numeric(instruction->cmd->next, instruction))
			clear_bash_and_exit(&bash, instruction->exit_status);
		finalize_exit(instruction, bash, arg_count);
	}
}

int	too_many_arg(int arg_count, t_instruction *inst)
{
	if (arg_count > 1)
	{
		inst->exit_status = 1;
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putendl_fd("bash: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	arg_is_not_numeric(t_token *cmd, t_instruction *inst)
{
	if (is_digit_only(cmd->data) != 0)
	{
		inst->exit_status = 2;
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putstr_fd("bash: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->data, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		return (1);
	}
	return (0);
}
