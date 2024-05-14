/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:25:18 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/14 20:44:16 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*init_bash(t_bash **bash, char **envp)
{
	if (bash == NULL)
		exit(EXIT_FAILURE);
	else
	{
		*bash = (t_bash *)malloc(sizeof(t_bash));
		if (!*bash)
			exit(EXIT_FAILURE);
		(*bash)->working_directory = NULL;
		(*bash)->exit_code = 0;
		(*bash)->env = init_env(envp);
		if ((*bash)->env == NULL)
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

	if (envp[0] == NULL)
		return (NULL);
}
