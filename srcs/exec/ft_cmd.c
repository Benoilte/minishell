/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2012/07/20 08:21:39 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/12 14:24:35 by bebrandt         ###   ########.fr       */
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
	{
		if (bash->ms_env == NULL)
			return (NULL);
		return (find_absolute_path(cmd, bash->ms_env));
	}
	else
		return (ft_strdup(cmd));
}

void	ft_cmd(char *sender, t_token *cmd, char **argv, t_bash *bash)
{
	char		*path;

	if (ft_strlen(cmd->data) == 0)
		clear_bash_and_exit(&bash, EXIT_SUCCESS);
	path = get_path(cmd->data, bash);
	if (!path)
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->data, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		clear_bash_and_exit(&bash, CMD_NOT_FOUND);
	}
	if (is_path_reachable(path, sender, cmd, bash))
	{
		set_sig_quit(DEFAULT);
		if (execve(path, argv, bash->ms_env) < 0)
		{
			free(path);
			print_error_and_exit("execve", cmd, CMD_NOT_EXEC, bash);
		}
	}
}

int	is_path_reachable(char *path, char *sender, t_token *cmd, t_bash *bash)
{
	struct stat	statbuf;

	if ((stat(path, &statbuf) == 0) && (statbuf.st_mode & S_IFDIR))
	{
		errno = EISDIR;
		free(path);
		print_error_and_exit(sender, cmd, CMD_NOT_EXEC, bash);
		return (0);
	}
	if (access(path, F_OK | X_OK))
	{
		free(path);
		print_error_and_exit(sender, cmd, CMD_NOT_EXEC, bash);
		return (0);
	}
	return (1);
}
