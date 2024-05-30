/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:35:50 by tmartin2          #+#    #+#             */
/*   Updated: 2024/05/30 12:13:54 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

// exec/sort_array.c

void	sort_array(t_instruction *instruction, t_env *env, char **envp);

// exec/ft_cmd.c

void ft_cmd(t_instruction *instruction, t_env *env, char **envp);

// exec/process.c

void child_process(t_instruction *instruction, t_env *env, char **envp, int prev_fd[2]);

#endif