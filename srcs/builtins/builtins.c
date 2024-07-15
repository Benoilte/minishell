/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:32:33 by tommartinel       #+#    #+#             */
/*   Updated: 2024/07/15 23:47:03 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

// TODO : structure bash en attande pour recupe le builtins
void	builtins(t_instruction *instruction, t_bash *bash)
{
	if (ft_strcmp(instruction->cmd->data, "cd") == 0)
	{
		cd(instruction, &bash->env);
		update_ms_env(bash);
	}
	else if (ft_strcmp(instruction->cmd->data, "export") == 0)
	{
		ft_export(bash, instruction);
		update_ms_env(bash);
	}
	else if (ft_strcmp(instruction->cmd->data, "unset") == 0)
	{
		ft_unset(bash, instruction);
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
}
