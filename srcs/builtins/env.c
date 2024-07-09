/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:42:09 by tmartin2          #+#    #+#             */
/*   Updated: 2024/07/09 08:38:41 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	ft_env(t_bash *bash, t_instruction *instruction)
{
	if (instruction->cmd->next == NULL)
		print_env(bash->ms_env);
	else if (env_has_cmd(instruction))
		exec_env_with_cmd(bash, instruction);
	else
		exec_env_without_cmd(bash->ms_env, instruction);
}

void	print_env(char **ms_env)
{
	int	i;

	if (!ms_env)
		return ;
	i = 0;
	while (ms_env[i])
	{
		ft_putendl_fd(ms_env[i], STDOUT_FILENO);
		i++;
	}
}

int	env_has_cmd(t_instruction *instruction)
{
	t_token	*current_cmd;

	current_cmd = instruction->cmd->next;
	while (current_cmd)
	{
		if (ft_strchr(current_cmd->data, '=') == NULL)
			return (FT_ENV_WITH_CMD);
		current_cmd = current_cmd->next;
	}
	return (FT_ENV_WITHOUT_CMD);
}

void	exec_env_with_cmd(t_bash *bash, t_instruction *inst)
{
	t_token			*current_cmd;

	current_cmd = inst->cmd->next;
	while (ft_strchr(current_cmd->data, '='))
		current_cmd = current_cmd->next;
	free(inst->cmd_array);
	if (fill_cmd_array(inst, current_cmd) == RETURN_FAILURE)
		inst->exit_status = 1;
	inst->pid = fork();
	if (inst->pid == -1)
	{
		perror("fork");
		inst->exit_status = 1;
	}
	else if (inst->pid == 0)
		exec_env_cmd(current_cmd, inst->cmd->next, inst->cmd_array, bash);
	else
	{
		inst->cmd->data_type ^= BUILTIN;
		if (wait_child_process(inst) == -1)
		{
			inst->cmd->data_type ^= BUILTIN;
			inst->exit_status = 1;
		}
	}
}

void	exec_env_without_cmd(char **ms_env, t_instruction *instruction)
{
	t_token	*current_cmd;

	current_cmd = instruction->cmd->next;
	print_env(ms_env);
	while (current_cmd)
	{
		ft_putendl_fd(current_cmd->data, STDOUT_FILENO);
		current_cmd = current_cmd->next;
	}
}
