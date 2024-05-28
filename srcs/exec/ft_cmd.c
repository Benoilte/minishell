/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:30:23 by tmartin2          #+#    #+#             */
/*   Updated: 2024/05/28 15:30:37 by tmartin2         ###   ########.fr       */
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
void ft_cmd(t_instruction *instruction, t_env *env, char **envp)
{
    char *cmd = instruction->cmd_array[0];
    char *path = find_path(cmd, env);
    if (!path)
    {
        fprintf(stderr, "path: error\n");
        _exit(EXIT_FAILURE); // Quitter si le chemin n'est pas trouvé
    }

    printf("Executing command via execve: %s\n", path);
    if (execve(path, instruction->cmd_array, envp) == -1)
    {
        perror("execve");
        free(path);
        _exit(EXIT_FAILURE);  // Utiliser _exit pour terminer le processus enfant
    }
}
