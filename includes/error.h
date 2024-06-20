/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 11:29:25 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/17 18:39:45 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

// memory allocation error

enum
{
	RETURN_SUCCESS,
	RETURN_FAILURE
};

enum
{
	SYNTAX_OK,
	SYNTAX_ERROR = 2
};

# define M_ALLOC "Error: Memory allocation"

// # define INSTRUCTION_EMPTY "syntax error command is empty after a pipe"

// Parsing redirection error

# define HERESTRING_NOT_IMPLEMENTED "syntax error Here Strings `<<<' redirection is \
not implemented"
# define UNEXPECTED_TOKEN "syntax error near unexpected token"

// Parsing command error

// Parsing shared error

# define UNCLOSED_QUOTES "syntax error unclosed quotes"

#endif
