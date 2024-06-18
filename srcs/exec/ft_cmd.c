/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:30:23 by tmartin2          #+#    #+#             */
/*   Updated: 2024/06/18 19:40:40 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static int	ft_strcmp(char *s1, char *s2)
{
	while ((*s1 != '\0') || (*s2 != '\0'))
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	return (0);
}
static char	*find_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*path;
	int		i;
    int     j;
	char	*part_path;
    char    *env_path_value;

    env_path_value = NULL;
    while(env)
    {
        if (ft_strcmp(env->name, "PATH") == 0)
        {
            env_path_value = env->value;
            break;
        }
        env = env->next;
    }
    if (!env_path_value)
        return (NULL);
    paths = ft_split(env_path_value, ':');
    if (!paths)
        return (NULL);
    i = 0;
    while(paths[i])
    {
        part_path = ft_strjoin(paths[i], "/");
        path = ft_strjoin(part_path, cmd);
        free(part_path);
        if (access(path, F_OK) == 0)
        {
            j = 0;
            while(paths[j])
                free(paths[j++]);
            free(paths);
            return(path);
        }
        free(path);
        i++;
    }
    i = 0;
    while(paths[i])
        free(paths[i++]);
    free(paths);
    return (NULL);
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
    char *cmd = instruction->cmd_array[0];
    char *path;
    int given;

    given = given_path(instruction, envp);
    if (given == 0)
    {
		set_sig_quit(DEFAULT);
        path = find_path(cmd, env);
        if (!path)
        {
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
