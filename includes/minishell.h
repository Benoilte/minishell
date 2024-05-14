/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:16:35 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/14 20:42:56 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// PERSONNAL LIB

# include "struct.h"
# include "../libft/includes/libft.h"

// main/minishell.c

// main/prompt.c

void	prompt(void);

//lexer/lexer.c

void	lexer(void);

// parser/parser.c

void	parser(void);

// builtins/builtins.c

void	builtins(void);

// exec/exec.c

void	exec(void);

// test/init.c

void	*init_bash(t_bash **bash, char **envp);
t_env	*init_env(char **envp);

// test/struct_utils.c

void	struct_utils(void);

// test/test.c

void	test(void);

#endif