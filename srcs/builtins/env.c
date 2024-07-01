/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:42:09 by tmartin2          #+#    #+#             */
/*   Updated: 2024/07/01 06:45:02 by bebrandt         ###   ########.fr       */
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

int	ft_env(t_bash *bash, t_instruction *instruction)
{
	if (instruction->cmd->next == NULL)
		return (print_env(bash->ms_env));
	else if (env_has_cmd(instruction))
		return (exec_env_with_cmd(bash, instruction));
	else
		return (exec_env_without_cmd(bash->ms_env, instruction));
	return (0);
}

int	print_env(char **ms_env)
{
	int	i;

	if (!ms_env)
		return (0);
	i = 0;
	while (ms_env[i])
	{
		ft_putendl_fd(ms_env[i], STDOUT_FILENO);
		i++;
	}
	return (0);
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

int	exec_env_with_cmd(t_bash *bash, t_instruction *instruction)
{
	t_token			*current_arg;
	t_token			*current_cmd;
	t_instruction	*tmp_inst;

	current_arg = instruction->cmd->next;
	while (ft_strchr(current_arg->data, '='))
		current_arg = current_arg->next;
	current_cmd = current_arg;
	free(instruction->cmd_array);
	if (fill_cmd_array(instruction, current_cmd) == RETURN_FAILURE)
		return (3);
	instruction->pid = fork();
	if (instruction->pid == 0)
	{
		set_sig_int(DEFAULT);
		current_arg = instruction->cmd->next;
		add_arg_env(bash, current_arg);
		start_execve("env", current_cmd->data, bash, instruction);
	}
	else
	{
		tmp_inst = instruction;
		while (tmp_inst != NULL)
		{
			waitpid(tmp_inst->pid, &tmp_inst->exit_status, 0);
			tmp_inst = tmp_inst->next;
		}
		set_exit_code(bash);
	}
	return (0);
}

int	exec_env_without_cmd(char **ms_env, t_instruction *instruction)
{
	t_token	*current_cmd;

	current_cmd = instruction->cmd->next;
	print_env(ms_env);
	while (current_cmd)
	{
		ft_putendl_fd(current_cmd->data, STDOUT_FILENO);
		current_cmd = current_cmd->next;
	}
	return (0);
}
