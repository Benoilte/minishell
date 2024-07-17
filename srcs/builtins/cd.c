/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:55:32 by tommartinel       #+#    #+#             */
/*   Updated: 2024/07/17 11:01:25 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	cd(t_instruction *instruction, t_env **env)
{
	char	*oldcwd;

	if (size_token(instruction->cmd) > 2)
	{
		ft_putendl_fd(CD_TOO_MANY_ARGUMENT, STDERR_FILENO);
		instruction->exit_status = 1;
		return ;
	}
	oldcwd = getcwd(NULL, 0);
	if (!oldcwd)
	{
		perror("getcwd() memory allocation");
		instruction->exit_status = 1;
		return ;
	}
	if (instruction->cmd->next == NULL)
		cd_go_home(instruction, env, oldcwd);
	else
		cd_move_dir(instruction, instruction->cmd->next->data, env, oldcwd);
}

void	cd_go_home(t_instruction *instruction, t_env **env, char *oldcwd)
{
	char	*home;

	if (name_exist(*env, "HOME"))
	{
		home = get_value(*env, "HOME");
		if (!home)
		{
			perror("get_value() memory aloccation");
			instruction->exit_status = 1;
		}
	}
	else
	{
		ft_putendl_fd(CD_HOME_NOT_SET, STDERR_FILENO);
		instruction->exit_status = 1;
		free(oldcwd);
		return ;
	}
	cd_move_dir(instruction, home, env, oldcwd);
}

void	cd_move_dir(t_instruction *inst, char *dir, t_env **env, char *oldcwd)
{
	char	*cwd;

	if (chdir(dir) != 0)
	{
		ft_chdir_error(dir, STDERR_FILENO);
		free(oldcwd);
		inst->exit_status = 1;
	}
	else
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			perror("getcwd() memory allocation");
			inst->exit_status = 1;
			return ;
		}
		set_cwd_env(inst, env, "OLDPWD", oldcwd);
		set_cwd_env(inst, env, "PWD", cwd);
	}
}

void	set_cwd_env(t_instruction *inst, t_env **env, char *name, char *value)
{
	char	*name_to_value;

	if (name_exist(*env, name))
		update_value(*env, name, value);
	else
	{
		name_to_value = get_name_to_value(name, value);
		free(value);
		if (!name_to_value)
		{
			perror("get_name_to_value() memory allocation");
			inst->exit_status = 1;
			return ;
		}
		add_back_env(env, new_env(name_to_value));
	}
}

void	ft_chdir_error(char *directory, int fd)
{
	ft_putstr_fd("cd: ", fd);
	ft_putstr_fd(directory, fd);
	ft_putstr_fd(": ", fd);
	ft_putendl_fd(strerror(errno), fd);
}
