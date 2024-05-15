/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:25:18 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/15 18:52:26 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_bash(t_bash **bash, char **envp)
{
	if (!bash)
		exit(EXIT_FAILURE);
	else
	{
		*bash = (t_bash *)malloc(sizeof(t_bash));
		if (!*bash)
			exit(EXIT_FAILURE);
		(*bash)->working_directory = NULL;
		(*bash)->exit_code = 0;
		(*bash)->env = init_env(envp);
		if (!(*bash)->env)
		{
			free(*bash);
			exit(EXIT_FAILURE);
		}
		(*bash)->instructions = NULL;
	}
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	t_env	*new;
	int		i;

	i = 0;
	env = NULL;
	if (envp[i] == NULL)
		return (NULL);
	while (envp[i])
	{
		new = new_env(envp[i]);
		if (!new)
			return (clear_env(&env));
		add_back_env(&env, new);
		i++;
	}
	return (env);
}
