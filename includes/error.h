/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 11:29:25 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/19 12:04:18 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

enum
{
	PARSING_OK,
	PARSING_ERROR
};

# define INSTRUCTION_EMPTY "syntax error command is empty after a pipe"

#endif