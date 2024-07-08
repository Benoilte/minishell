/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:30:23 by tmartin2          #+#    #+#             */
/*   Updated: 2024/07/06 14:25:46 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static char	*find_absolute_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

char	*get_path(char *cmd, t_bash *bash)
{
	if (ft_strchr(cmd, '/') == NULL)
		return (find_absolute_path(cmd, bash->ms_env));
	else
		return (ft_strdup(cmd));
}

void	ft_cmd(char *sender, char *cmd, char **argv, t_bash *bash)
{
	char		*path;
	struct stat	statbuf;

	path = get_path(cmd, bash);
	if (!path)
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		clear_bash_and_exit(&bash, CMD_NOT_FOUND);
	}
	if ((stat(path, &statbuf) == 0) && (statbuf.st_mode & S_IFDIR))
	{
		errno = EISDIR;
		free(path);
		print_cmd_error_and_exit(sender, cmd, CMD_NOT_EXEC, bash);
	}
	if (access(path, F_OK | X_OK))
	{
		free(path);
		print_cmd_error_and_exit(sender, cmd, CMD_NOT_EXEC, bash);
	}
	set_sig_quit(DEFAULT);
	if (execve(path, argv, bash->ms_env) < 0)
	{
		free(path);
		print_cmd_error_and_exit("execve", cmd, CMD_NOT_EXEC, bash);
	}
}
