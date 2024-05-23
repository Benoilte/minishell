/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:35:11 by tmartin2          #+#    #+#             */
/*   Updated: 2024/05/23 15:34:37 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void sort_array(t_instruction *instruction)
{
    if (instruction == NULL) {
        fprintf(stderr, "Erreur : instruction est NULL\n");
        return;
    }

    if (instruction->cmd_array == NULL) {
        fprintf(stderr, "Erreur : cmd_array est NULL\n");
        return;
    }

    int i = 0;
    while (instruction->cmd_array[i] != NULL)
    {
        printf("tab : %s\n", instruction->cmd_array[i]); // Ajout d'un saut de ligne pour une meilleure lisibilité
        i++;
    }
}
