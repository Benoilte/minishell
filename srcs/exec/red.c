/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:16:17 by tmartin2          #+#    #+#             */
/*   Updated: 2024/06/11 13:47:43 by tmartin2         ###   ########.fr       */
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
void here_doc(t_instruction *instruction)
{
    char *limiter;
    pid_t reader;
    char *line;

    limiter = instruction->red->option;
    if (pipe(instruction->fd) == -1)
        perror("pipe");
    reader = fork();
    if (reader == 0)
    {
        close(instruction->fd[0]);
        while(write(1, "> ", 2) && ft_get_next_line(&line))
        {
            if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
                exit(EXIT_SUCCESS);
            write(instruction->fd[1], line, ft_strlen(line));
        }
    }
    else
    {
        close(instruction->fd[1]);
        dup2(instruction->fd[0], STDIN_FILENO);
        wait(NULL);
    }
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
