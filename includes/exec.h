/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:35:50 by tmartin2          #+#    #+#             */
/*   Updated: 2024/06/20 15:39:20 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parser.h"
// exec/sort_array.c

void	sort_red(t_instruction *instruction);

// exec/ft_cmd.c

void ft_cmd(t_instruction *instruction, t_env *env, char **envp);
int given_path(t_instruction *instruction, char **envp);

// exec/process.c

void ft_exit(t_instruction *instruction, t_bash *bash);
void child_process(t_instruction *instruction, t_bash *bash, char **envp);
void parent_process(t_instruction *instruction);

// exec/red.c

void red(t_instruction *instruction);
int open_file(char *red, t_token *token);
void here_doc(t_instruction *instruction);

// exec/sort_cmd_builtin

void sort_cmd_builtin(t_instruction *instruction, t_bash *bash, char **envp);

// exec/utils_exec.c

int	ft_get_next_line(char **line);
int	ft_strcmp(char *s1, char *s2);

#endif