/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:25:18 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/15 00:36:28 by bebrandt         ###   ########.fr       */
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
	t_env	*new;
	char	**split;
	int		i;

	i = 0;
	if (envp[i] == NULL)
		return (NULL);
	while (envp[i])
	{
		split = ft_split(envp[i], '=');
		if (split == NULL)
			clear_env(env);
	}
	return (env);
}
