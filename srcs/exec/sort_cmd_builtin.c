/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cmd_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:09:32 by tmartin2          #+#    #+#             */
/*   Updated: 2024/07/17 12:02:05 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	sort_cmd_builtin(t_instruction *instruction, t_bash *bash)
{
	if (instruction->cmd == NULL)
		clear_bash_and_exit(&bash, EXIT_SUCCESS);
	else if (instruction->cmd->data_type & BUILTIN)
		builtins(instruction, bash);
	else if (instruction->cmd->data_type & CMD)
		ft_cmd("minishell", instruction->cmd, instruction->cmd_array, bash);
}
