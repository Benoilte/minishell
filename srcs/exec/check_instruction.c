/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:56:23 by tmartin2          #+#    #+#             */
/*   Updated: 2024/05/21 15:37:44 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

char	*find_path(char *cmd, char **envp)
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
char *check_instruction(t_instruction *cmd, char **envp)
{
    t_instruction *current;
    char *cmd_path;
    char *envp;
    int i;

    i = 0;
    current = *cmd;
    while (current != NULL)
    {
        if (current->cmd->data && current->cmd)
        {
            cmd_path = find_path(current->cmd->data, envp);
            if (!cmd_path)
            {
                while(current->cmd->data[++i])
                    free(current->cmd->data[i]);
                free(current->cmd->data);
                free(current->cmd);
            }
            else if (cmd_path)
                return (cmd_path);
        }
    }
    return (NULL);
}
