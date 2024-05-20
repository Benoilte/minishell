/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:48:16 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/19 23:59:17 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// MINISHELL HEADER

# include "minishell.h"

// parser/parser.c

int		check_instruction(t_bash *bash, t_instruction *instruction);
void	update_instruction(t_bash *bash, t_instruction *instruction);

// parser/parser_check_redirections.c

int		check_redirections(t_token *red);
int		check_data_redirection(char *data, int type);
int		check_opt_redirection(char *option, int type);
int		is_unexpected_token(char c);

// parser/parser_check_cmd.c

// parser/parser_check_utils.c

int		type_equal_to(int flag, int type);
int		check_closed_quotes(char *data);
int		check_text_out_of_quotes(char *data);
int		print_parsing_error_msg(char *msg, char *token_str, char token_c);

#endif
