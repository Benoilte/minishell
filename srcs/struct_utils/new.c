/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 22:30:56 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/20 14:56:21 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// name_to_value should be equal to name=value || name= || name
t_env	*new_env(char *name_to_value)
{
	t_env	*env;
	int		i;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	i = 0;
	while (name_to_value[i] && name_to_value[i] != '=')
		i++;
	env->name = ft_substr(name_to_value, 0, i);
	if (!env->name)
	{
		free(env);
		return (NULL);
	}
	i++;
	env->value = ft_substr(name_to_value, i, ft_strlen(name_to_value) - i);
	if (!env->value)
	{
		free(env->name);
		free(env);
		return (NULL);
	}
	env->next = NULL;
	return (env);
}

t_instruction	*new_instruction(void)
{
	t_instruction	*instruction;

	instruction = (t_instruction *)malloc(sizeof(t_instruction));
	if (!instruction)
		return (NULL);
	instruction->red = NULL;
	instruction->cmd = NULL;
	instruction->cmd_array = NULL;
	instruction->next = NULL;
	return (instruction);
}

t_token	*new_token(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->data = NULL;
	token->option = NULL;
	token->data_type = 0;
	token->option_type = 0;
	token->next = NULL;
	return (token);
}
