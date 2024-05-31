/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:16:17 by tmartin2          #+#    #+#             */
/*   Updated: 2024/05/31 17:59:46 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int open_file(char *red, int i)
{
    int file;

    file = -1;
    if (i == OUTPUT_TRUNCATE)
        file = open(red,  O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (i == OUTPUT_APPEND)
        file = open(red,  O_WRONLY | O_CREAT | O_APPEND, 0777);
    if (i == INPUT)
        file = open(red, O_RDONLY);
    if (file < 0)
        perror("Error open file\n");
    return (file);
}

void red(t_instruction *instruction)
{
    char *red;
    int file;
    int i;
    
    file = 0;
    i = instruction->red->data_type;
    red = instruction->red->option;
    if (i == OUTPUT_TRUNCATE)
    {
        file = open_file(red, OUTPUT_TRUNCATE);
        dup2(file, STDOUT_FILENO);
        close(file);
    }
    if (i == OUTPUT_APPEND)
    {
        file = open_file(red, OUTPUT_APPEND);
        dup2(file, STDOUT_FILENO);
        close(file);        
    }
    if (i == INPUT)
    {
        file = open_file(red, INPUT);
        dup2(file, STDIN_FILENO);
        close(file);
    }
}
