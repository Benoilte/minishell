/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:00:59 by tmartin2          #+#    #+#             */
/*   Updated: 2024/05/27 10:43:23 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void pwd(t_instruction *instruction)
{
    (void)instruction;
    char *cwd;

        cwd = getcwd(NULL, 0);
        if (cwd == NULL)
        {
            perror("getcwd");
            return ;
        }
        printf("%s\n", cwd);
}
