/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:30:23 by tmartin2          #+#    #+#             */
/*   Updated: 2024/06/21 16:29:15 by bebrandt         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
            exit(CMD_NOT_EXEC);
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
            printf("minishell: command not found: %s\n", instruction->cmd_array[0]);
            exit(CMD_NOT_FOUND); // Quitter si le chemin n'est pas trouvé
        }
        if (execve(path, instruction->cmd_array, envp) < 0)
        {
            perror("execve");
            free(path);
            exit(CMD_NOT_EXEC);  // Utiliser exit pour terminer le processus en cas d'erreur
        }
        free(path);
    }
    exit(EXIT_SUCCESS);
}
