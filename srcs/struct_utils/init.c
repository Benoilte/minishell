/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:25:18 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/18 16:37:02 by bebrandt         ###   ########.fr       */
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
		(*bash)->sequence = NULL;
		(*bash)->exit_code = 0;
		(*bash)->env = init_env(*bash, envp);
		(*bash)->instruction = NULL;
	}
}

t_env	*init_env(t_bash *bash, char **envp)
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
		{
			clear_bash(&bash);
			exit(EXIT_FAILURE);
		}
		add_back_env(&env, new);
		i++;
	}
	return (env);
}

t_instruction	*init_instruction(t_bash *bash)
{
	t_instruction	*new;

	new = new_instruction();
	if (!new)
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	return (new);
}

t_token	*init_token(t_bash *bash)
{
	t_token	*new;

	new = new_token();
	if (!new)
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	return (new);
}
