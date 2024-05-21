/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:15:42 by tmartin2          #+#    #+#             */
/*   Updated: 2024/05/20 13:17:05 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void cd(t_bash *bash)
{
    char *directory;

    if (ft_strncmp(bash->sequence, "cd", 2) == 0)
    {
        directory = bash->sequence + 2;
        while (*directory == ' ')
            directory++;
        if (*directory == '\0')
        {
            directory = getenv("HOME");
            if (directory == NULL)
            {
                fprintf(stderr, "cd : HOME not set\n");
                return ;
            }
        }
        if (chdir(directory) != 0)
        {
            fprintf(stderr, "cd: %s: %s\n", directory, strerror(errno));  
            EXIT_FAILURE;
        }
    }
}
