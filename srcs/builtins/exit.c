/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:22:50 by tmartin2          #+#    #+#             */
/*   Updated: 2024/05/20 13:31:39 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

//fonction pour supprimer tout les espace
void trim(t_bash *bash)
{
    char *str = bash->sequence;
    int len = ft_strlen(str);
    int i = 0;
    int j = 0;
    
    while (i < len)
    {
        if (str[i] != ' ')
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
}
int ft_exit(t_bash *bash)
{
    int exit = 0;
    trim(bash);
    if (ft_strcmp(bash->sequence, "exit") == 0)
    {
        exit = 1;
    }
    return (exit);
}