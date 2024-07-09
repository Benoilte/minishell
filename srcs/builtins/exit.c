/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:24:31 by tommartinel       #+#    #+#             */
/*   Updated: 2024/07/09 22:09:11 by bebrandt         ###   ########.fr       */
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
	if (instruction->save_stdout != -1)
	{
		dup2(instruction->save_stdout, STDOUT_FILENO);
		close(instruction->save_stdout);
		instruction->save_stdout = -1;
	}
	if (arg_count == 1)
		bash->exit_code = ft_atoi(instruction->cmd->next->data);
	printf("exit\n");
	clear_bash_and_exit(&bash, bash->exit_code);
}

void	ft_exit(t_instruction *instruction, t_bash *bash)
{
	t_token		*instruction_tmp;
	int			arg_count;

	instruction_tmp = instruction->red;
	if (instruction->cmd != NULL && instruction->cmd->data != NULL
		&& strcmp(instruction->cmd->data, "exit") == 0)
	{
		arg_count = count_arguments(instruction->cmd);
		if (handle_exit_error(arg_count, instruction->cmd->next, instruction))
			return ;
		instruction->red = instruction_tmp;
		finalize_exit(instruction, bash, arg_count);
	}
}

int	handle_exit_error(int arg_count, t_token *red, t_instruction *instr)
{
	if (arg_count > 1)
	{
		instr->exit_status = 1;
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putendl_fd("bash: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	if (arg_count == 1 && red != NULL && is_digit_only(red->data) != 0)
	{
		instr->exit_status = 1;
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putstr_fd("bash: exit: ", STDERR_FILENO);
		ft_putstr_fd(instr->cmd->next->data, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		return (1);
	}
	return (0);
}
