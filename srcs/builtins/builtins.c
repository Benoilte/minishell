/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:54:12 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/02 18:54:33 by bebrandt         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/builtins.h"

// TODO : structure bash en attande pour recupe le builtins
void	builtins(t_instruction *instruction, t_env *env, t_bash *bash)
{
	if (ft_strcmp(instruction->cmd->data, "cd") == 0)
	{
		cd(instruction, &bash->env);
		update_ms_env(bash);
	}
	else if (ft_strcmp(instruction->cmd->data, "export") == 0)
	{
		ft_export(env, instruction);
		update_ms_env(bash);
	}
	else if (ft_strcmp(instruction->cmd->data, "unset") == 0)
	{
		ft_unset(&env, instruction);
		update_ms_env(bash);
	}
	else if (ft_strcmp(instruction->cmd->data, "echo") == 0)
		echo(instruction);
	else if (ft_strcmp(instruction->cmd->data, "pwd") == 0)
		pwd(instruction);
	else if (ft_strcmp(instruction->cmd->data, "env") == 0)
		ft_env(bash, instruction);
	else if (ft_strcmp(instruction->cmd->data, "exit") == 0)
		ft_exit(instruction, bash);
	reset_stdout(instruction);
}

void	reset_stdout(t_instruction *curr_inst)
{
	if (curr_inst->save_stdout != -1)
	{
		if (dup2(curr_inst->save_stdout, STDOUT_FILENO) < 0)
		{
			curr_inst->exit_status = 1;
			print_cmd_error("dup2", curr_inst->cmd->data);
		}
		if (close(curr_inst->save_stdout) < 0)
		{
			curr_inst->exit_status = 1;
			print_cmd_error("close", curr_inst->cmd->data);
		}
		curr_inst->save_stdout = -1;
	}
}
