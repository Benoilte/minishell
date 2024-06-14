/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:54:12 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/14 12:58:57 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

// TODO : structure bash en attande pour recupe le builtins
void builtins(t_instruction *instruction, t_env *env)
{
	if (ft_strcmp(instruction->cmd->data, "pwd") == 0)
		pwd(instruction);
	if (ft_strcmp(instruction->cmd->data, "cd") == 0)
		cd(instruction);
	if (ft_strcmp(instruction->cmd->data, "echo") == 0)
		echo(instruction);
	if (ft_strcmp(instruction->cmd->data, "export") == 0)
	 	ft_export(env, instruction);
	if (ft_strcmp(instruction->cmd->data, "unset") == 0)
		ft_unset(&env, instruction);
	if (ft_strcmp(instruction->cmd->data, "env") == 0)
		print_env(env, instruction);
}
