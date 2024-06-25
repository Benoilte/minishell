/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:15:42 by tmartin2          #+#    #+#             */
/*   Updated: 2024/06/25 20:10:07 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	cd(t_instruction *instruction, t_env *env)
{
	char	*directory;

	if (size_token(instruction->cmd) > 2)
	{
		ft_putendl_fd(CD_TOO_MANY_ARGUMENT, STDERR_FILENO);
		instruction->exit_status = 1;
		return ;
	}
	if (instruction->cmd->next != NULL)
		directory = ft_strdup(instruction->cmd->next->data);
	else
	{
		directory = get_value(env, "HOME");
		if (directory == NULL)
		{
			ft_putendl_fd(CD_HOME_NOT_SET, STDERR_FILENO);
			return ;
		}
	}
	if (chdir(directory) != 0)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(directory, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		free(directory);
	}
	else
		set_pwd(env);
	free(directory);
}

void	set_pwd(t_env *env)
{
	char	*wd;

	wd = getcwd(NULL, 0);
	if (!wd)
	{
		perror("getcwd");
		return ;
	}
	if (name_exist(env, "PWD"))
		update_value(env, "PWD", wd);
}

void	ft_chdir_error(char *directory)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(directory, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void	ft_dir_error(char *dir, char *error_msg, int fd)
{
	ft_putstr_fd("minishell: cd: /bin/ls: ", fd);
	ft_putstr_fd(dir, fd);
	ft_putstr_fd(": ", fd);
	ft_putendl_fd(error_msg, fd);
}
