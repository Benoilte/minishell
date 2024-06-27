/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:25:27 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/27 21:59:38 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	*clear_ms_env(char **ms_env)
{
	int	i;

	i = 0;
	while (ms_env[i])
	{
		free(ms_env[i]);
		i++;
	}
	free(ms_env);
	ms_env = NULL;
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
		clear->prev = NULL;
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
