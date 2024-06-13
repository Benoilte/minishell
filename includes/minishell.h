/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:16:35 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/13 12:52:48 by bebrandt         ###   ########.fr       */
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
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

// main/minishell.c

void	print_how_to_use_minishell(void);

// main/interactive_minishell.c

void	start_interactive_minishell(t_bash *bash);
void	set_signal_action(void);
void	signal_handler(int signum);

// main/non_interactive_minishell.c

void	start_non_interactive_minishell(t_bash *bash, char *file);
char	*get_sequence(int fd);

// main/minishell_utils.c

int		type_equal_to(int flag, int type);

// main/prompt.c


//lexer/lexer.c

int		lexing(t_bash *bash, char *sequence);

// parser/parser.c

int		parsing(t_bash *bash);

// builtins/builtins.c

void builtins(t_instruction *instruction, t_env *env, t_bash *bash);

// exec/exec.c

void	exec(t_instruction *instruction, t_bash *bash, char **envp);

// test/test.c

void	test_print_env(t_env *env);
void	test_print_instruction(t_instruction *instruction);
void	test_print_cmd_token(t_token *token);
void	test_print_red_token(t_token *token);
void	test_print_cmd_array(char **cmd_array);

#endif
