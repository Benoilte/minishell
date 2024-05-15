/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:25:27 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/15 13:56:53 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*clear_bash(t_bash **bash)
{
	if ((*bash)->working_directory)
		free((*bash)->working_directory);
	if ((*bash)->instructions)
		free((*bash)->instructions);
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
