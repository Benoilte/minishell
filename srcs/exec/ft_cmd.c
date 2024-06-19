/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tommartinelli <tommartinelli@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:30:23 by tmartin2          #+#    #+#             */
/*   Updated: 2024/06/19 14:46:15 by tommartinel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static char	*find_path(char *cmd, char **envp)
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
int given_path(t_instruction *instruction, char **envp)
{
    if (ft_strchr(instruction->cmd_array[0], '/') != NULL)
    {
		set_sig_quit(DEFAULT);
        if (execve(instruction->cmd_array[0], instruction->cmd_array, envp) < 0)
        {
            printf("zsh: command not found: %s\n", instruction->cmd_array[0]);
            exit(EXIT_FAILURE);
        }
        return 1;
    }
    return 0;
}

void ft_cmd(t_instruction *instruction, t_env *env, char **envp)
{
    (void)env;
    char *cmd = instruction->cmd_array[0];
    char *path;
    int given;

    given = given_path(instruction, envp);
    if (given == 0)
    {
		set_sig_quit(DEFAULT);
        path = find_path(cmd, envp);
        if (!path)
        {
            printf("cmd : %s\n", cmd);
            printf("zsh: command not found: %s\n", instruction->cmd_array[0]);
            exit(EXIT_FAILURE); // Quitter si le chemin n'est pas trouvé
        }
        if (execve(path, instruction->cmd_array, envp) < 0)
        {
            perror("execve");
            free(path);
            exit(EXIT_FAILURE);  // Utiliser exit pour terminer le processus en cas d'erreur
        }
        free(path);
    }
    exit(EXIT_SUCCESS);
}
