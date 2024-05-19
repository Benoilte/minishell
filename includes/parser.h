/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:48:16 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/19 13:53:10 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// MINISHELL HEADER

# include "minishell.h"

// parser/parser.c

int		parsing(t_bash *bash);
int		check_instruction(t_bash *bash, t_instruction *instruction);
void	update_instruction(t_bash *bash, t_instruction *instruction);

// parser/parser_check_redirections.c

int		check_redirections(t_token *red);
int		check_data_redirection(char *data, int type);
int		check_opt_redirection(char *option, int type);

// parser/parser_check_cmd.c

// parser/parser_check_utils.c

#endif