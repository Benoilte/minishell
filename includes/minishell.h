/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:16:35 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/23 15:41:54 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// PERSONNAL LIB

# include "struct.h"
# include "error.h"
# include "../libft/includes/libft.h"

// readline lib

# include <readline/readline.h>
# include <readline/history.h>

// other lib

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

// main/minishell.c

// main/prompt.c

void	prompt(void);

//lexer/lexer.c

void	lexing(t_bash *bash, char *sequence);

// parser/parser.c

int		parsing(t_bash *bash);

// builtins/builtins.c

void builtins(t_bash *bash);

// exec/exec.c

void	exec(t_bash *bash);

// test/test.c

void	test_print_env(t_env *env);
void	test_print_instruction(t_instruction *instruction);
void	test_print_cmd_token(t_token *token);
void	test_print_red_token(t_token *token);
void	test_print_cmd_array(char **cmd_array);

#endif
