/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:15:42 by tmartin2          #+#    #+#             */
/*   Updated: 2024/06/25 18:45:02 by bebrandt         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/builtins.h"

void	cd(t_instruction *instruction, t_env *env)
{
	char	*directory;

	if (size_token(instruction->cmd) > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		instruction->exit_status = 1;
		return ;
	}
	if (instruction->cmd_array[1] != NULL)
		directory = instruction->cmd_array[1];
	else
	{
		directory = get_value(env, "HOME");
		if (directory == NULL)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			return ;
		}
	}
	if (chdir(directory))
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(directory, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	else
	{
		set_pwd(env, directory);
	}
}

void	set_pwd(t_env *env, char *directory)
{
	if (name_exist(env, "PWD"))
	{
		printf("directory: %s\n", directory);
		rl_on_new_line();
		rl_replace_line("", 0);
		update_value(env, "PWD", directory);
	}
}
