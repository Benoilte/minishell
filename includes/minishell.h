/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:29:25 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/15 23:47:26 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// readline lib

# include <readline/readline.h>
# include <readline/history.h>

// extern lib

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>

// PERSONNAL LIB

# include "ms_signal.h"
# include "struct.h"
# include "error.h"
# include "../libft/includes/libft.h"
# include "exec.h"
# include "builtins.h"
# include "parser.h"

// main/minishell.c

void	print_how_to_use_minishell(void);

// main/interactive_minishell.c

void	start_interactive_minishell(t_bash *bash, int debug);

// main/non_interactive_minishell.c

void	start_non_interactive_minishell(t_bash *bash, char *file, int debug);
int		is_wrong_file_format(char *file, int fd);
char	*get_sequence(int fd);
int		open_arg_file(char *arg_file);

// main/minishell_utils.c

int		type_equal_to(int flag, int type);
void	check_sequence_and_execution(t_bash *bash, int debug);

//lexer/lexer.c

int		lexing(t_bash *bash, char *sequence);

// parser/parser.c

int		parsing(t_bash *bash);
int		sequence_is_filled(t_instruction *instruction);

// builtins/builtins.c

void	builtins(t_instruction *instruction, t_bash *bash);

// exec/exec.c

void	exec(t_instruction *instruction, t_bash *bash, char **envp);

// test/test.c

void	test_print_env(t_env *env);
void	test_print_instruction(t_instruction *instruction);
void	test_print_cmd_token(t_token *token);
void	test_print_red_token(t_token *token);
void	test_print_cmd_array(char **cmd_array);

// test/test_utils.c

void	test_print_ms_env(char **ms_env);

#endif
