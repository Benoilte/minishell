/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:01:20 by tmartin2          #+#    #+#             */
/*   Updated: 2024/05/21 15:37:48 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

// ./exec/exec.c

void ft_cmd(t_bash *bash, char **envp);

// ./exec/check_instruction.c

char *check_instruction(t_instruction *cmd, char **envp);
char	*find_path(char *cmd, char **envp);

#endif