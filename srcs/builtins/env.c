/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:42:09 by tmartin2          #+#    #+#             */
/*   Updated: 2024/07/01 17:00:12 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

/*
Remplacer élément char **envp de la structure bash par char **ms_env

	- ms_env sera une copie de la structure t_env au format [[n=v][n=v][NULL]]

	- celle ci devra être mise à jour chaque fois qu'on effectue
	  une modification de la structure t_env avec export, unset, cd
	  et sera utilisée à chaque fois qu'on execute la fonction execve()
	  pour appeler les commande avec l'environnement du minishell

Si aucun argument => imprimer les variables d'environnemnt sur le STDOUT

Si argument, trouver le premier qui n'est pas au format name=value
	- Contrôler si c'est un programme existant, avec la variable PATH

	- Si inexistant retourner une erreur et sortir de la fonction
	  avec exit_status correspondant

	- Si commande existante
		- Export paramètre précédent au format name=value

		- Reconfigurer la cmd_array de la structure instruction

		- Créer un process enfant et executer la commande avec execve en donnant
		  en argument l'environement précédement modifié

		- Une fois le process enfant terminé, correctement ou avec une erreur
		  d'execution unset les paramètre précédemment exporter

		- Reconfiguer la variable ms_env

sortir de la commande env() avec exit status correspondant
*/

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
		exec_env_cmd(current_cmd->data, inst->cmd->next, inst->cmd_array, bash);
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
