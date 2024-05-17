/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:16:35 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/17 16:36:58 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// PERSONNAL LIB

# include "struct.h"
# include "../libft/includes/libft.h"

// readline lib

#include <readline/readline.h>
#include <readline/history.h>

// binary flags to define a cmd type

enum
{
	INPUT = 1 ,
	HEREDOC = 2,
	OUTPUT_TRUNCATE = 4,
	OUTPUT_APPEND = 8,
	D_QUOTES = 16,
	S_QUOTES = 32,
	BUILTIN = 64,
	CMD = 128,
	WORD = 256
};

// main/minishell.c

// main/prompt.c

void	prompt(void);

//lexer/lexer.c

void	lexing(t_bash *bash, char *sequence);
void	set_redirection(t_bash *bash, char *sequence, int *i);
void	set_quotes(t_bash *bash, char *sequence, int *i, int *cmd);
void	set_pipe(t_bash *bash, int *i, int *cmd);
void	set_word(t_bash *bash, char *sequence, int *i, int *cmd);

// parser/parser.c

void	parser(void);

// builtins/builtins.c

void	builtins(void);

// exec/exec.c

void	exec(void);

// test/test.c

void	test_print_env(t_env *env);

#endif
