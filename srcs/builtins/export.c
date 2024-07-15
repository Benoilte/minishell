/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:04:33 by tmartin2          #+#    #+#             */
/*   Updated: 2024/07/15 23:21:38 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	set_env_var_liste(t_env *env, char *envp)
{
	t_env	*new;

	new = new_env(envp);
	if (!new)
		return (0);
	if (name_exist(env, new->name))
	{
		update_value(env, new->name, new->value);
		free(new->name);
		free(new);
		return (1);
	}
	add_back_env(&env, new);
	return (1);
}

void	print_env_vars(t_env **sorted_env)
{
	int	i;

	i = 0;
	while (sorted_env[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd((sorted_env[i])->name, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
		ft_putstr_fd((sorted_env[i])->value, STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

void	handle_export_args(t_env *env, t_instruction *instruction)
{
	int	start_index;

	start_index = 1;
	while (instruction->cmd_array[start_index] != NULL)
	{
		if (check_name_format(instruction->cmd_array[start_index]) == 1)
		{
			instruction->exit_status = 1;
			print_export_error_identifier(instruction->cmd_array[start_index]);
		}
		else if (ft_strchr(instruction->cmd_array[start_index], '=') != NULL)
		{
			if (!set_env_var_liste(env, instruction->cmd_array[start_index]))
			{
				instruction->exit_status = 1;
				print_cmd_error("export", instruction->cmd);
			}
		}
		start_index++;
	}
}

void	ft_export(t_env *env, t_instruction *instruction)
{
	t_env	**env_sorted;

	if (instruction->cmd_array[1] == NULL)
	{
		env_sorted = sort_export_env(env);
		if (!env_sorted)
			print_cmd_error("export", instruction->cmd);
		print_env_vars(env_sorted);
		free(env_sorted);
	}
	else
		handle_export_args(env, instruction);
}

int	check_name_format(char *name)
{
	int	i;

	i = 0;
	if (ft_isalpha(name[i]) == 0)
		return (1);
	while (name[i] && (name[i] != '='))
	{
		if ((ft_isalnum(name[i]) == 0) && name[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
