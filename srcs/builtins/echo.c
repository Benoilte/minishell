/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:54:13 by tmartin2          #+#    #+#             */
/*   Updated: 2024/05/20 13:58:54 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void echo(t_bash *bash)
{
    char *rl;
    char *msg;
    int new_line;
    
    if (ft_strncmp(bash->sequence, "echo ", 5) == 0)
    {
        rl = bash->sequence;
        msg = rl + 5;
        new_line = 1;
        if (ft_strncmp(msg, "-n ", 3) == 0)
        {
            new_line = 0;
            msg += 3;
        }
        printf("%s", msg);
        if (new_line)
            printf("\n");
    }
}

