/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:25:27 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/18 18:57:53 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*clear_bash_and_exit(t_bash **bash, int exit_code)
{
	set_terminal(RESET);
	clear_bash(bash);
	exit(exit_code);
}

void	*clear_bash(t_bash **bash)
{
	if ((*bash)->working_directory)
		free((*bash)->working_directory);
	if ((*bash)->sequence)
		free((*bash)->sequence);
	if ((*bash)->instruction)
		clear_instruction(&(*bash)->instruction);
	if ((*bash)->env)
		clear_env(&(*bash)->env);
	free(*bash);
	return (NULL);
}

void	*clear_env(t_env **env)
{
	t_env	*clear;
	t_env	*next;

	clear = *env;
	*env = NULL;
	while (clear != NULL)
	{
		next = clear->next;
		if (clear->name)
			free(clear->name);
		if (clear->value)
			free(clear->value);
		free(clear);
		clear = next;
	}
	return (NULL);
}

void	*clear_instruction(t_instruction **instruction)
{
	t_instruction	*clear;
	t_instruction	*next;

	clear = *instruction;
	*instruction = NULL;
	while (clear != NULL)
	{
		next = clear->next;
		if ((clear)->red)
			clear_token(&(clear)->red);
		if ((clear)->cmd)
			clear_token(&(clear)->cmd);
		if (clear->cmd_array)
			free(clear->cmd_array);
		free(clear);
		clear = next;
	}
	return (NULL);
}

void	*clear_token(t_token **token)
{
	t_token	*clear;
	t_token	*next;

	clear = *token;
	*token = NULL;
	while (clear != NULL)
	{
		next = clear->next;
		if (clear->data)
			free(clear->data);
		if (clear->option)
			free(clear->option);
		free(clear);
		clear = next;
	}
	return (NULL);
}
