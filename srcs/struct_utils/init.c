/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:25:18 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/28 19:39:00 by bebrandt         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
		(*bash)->env = init_env(envp);
		(*bash)->ms_env = init_ms_env((*bash)->env);
		(*bash)->instruction = NULL;
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
		{
			clear_env(&env);
			ft_printf("%s init env\n", M_ALLOC);
			return (NULL);
		}
		add_back_env(&env, new);
		i++;
	}
	return (env);
}

t_instruction	*init_instruction(void)
{
	t_instruction	*new;

	new = new_instruction();
	if (!new)
	{
		ft_printf("%s init instruction\n", M_ALLOC);
		return (NULL);
	}
	return (new);
}

t_token	*init_token(void)
{
	t_token	*new;

	new = new_token();
	if (!new)
	{
		ft_printf("%s init token\n", M_ALLOC);
		return (NULL);
	}
	return (new);
}

char	**init_ms_env(t_env *env)
{
	int		i;
	char	**ms_env;
	t_env	*tmp_env;

	if (size_env(env) == 0)
		return (NULL);
	ms_env = (char **)ft_calloc(size_env(env) + 1, sizeof(char *));
	if (!ms_env)
		return (NULL);
	tmp_env = env;
	i = 0;
	while (tmp_env)
	{
		ms_env[i++] = get_name_to_value(tmp_env->name, tmp_env->value);
		if (!ms_env)
		{
			clear_ms_env(ms_env);
			return (NULL);
		}
		tmp_env = tmp_env->next;
	}
	return (ms_env);
}
