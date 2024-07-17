/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:12:33 by tmartin2          #+#    #+#             */
/*   Updated: 2024/07/17 21:15:46 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	check_identifier_format(char *name);
static void	print_unset_error_identifier(char *name_to_value);
static void	unset_identifier(t_bash *bash, char *identifier);

static void	delete_env_node(t_env **env, t_env *prev, t_env *current)
{
	if (prev == NULL)
		*env = current->next;
	else
		prev->next = current->next;
	free(current->name);
	free(current->value);
	free(current);
}

void	ft_unset(t_bash *bash, t_instruction *instruction)
{
	int		i;

	i = 1;
	while (instruction->cmd_array[i] != NULL)
	{
		if (check_identifier_format(instruction->cmd_array[i]))
		{
			instruction->exit_status = 1;
			print_unset_error_identifier(instruction->cmd_array[i]);
		}
		else
			unset_identifier(bash, instruction->cmd_array[i]);
		i++;
	}
}

static int	check_identifier_format(char *name)
{
	int	i;

	i = 0;
	if ((ft_isalpha(name[i]) == 0) && (name[i] != '_'))
		return (1);
	while (name[i])
	{
		if ((ft_isalnum(name[i]) == 0) && name[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static void	print_unset_error_identifier(char *identifier)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(identifier, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

static void	unset_identifier(t_bash *bash, char *identifier)
{
	t_env	*current_env;
	t_env	*prev_env;

	current_env = bash->env;
	prev_env = NULL;
	while (current_env)
	{
		if (ft_strcmp(current_env->name, identifier) == 0)
		{
			delete_env_node(&(bash->env), prev_env, current_env);
			break ;
		}
		prev_env = current_env;
		current_env = current_env->next;
	}
}
