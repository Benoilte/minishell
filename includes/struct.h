/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:12:23 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/14 17:20:16 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_sequence
{
	char					*working_directory;
	char					*env;
	struct s_instructions	*instructions;
}							t_sequence;

typedef struct s_instructions
{
	struct s_token_red		*red;
	struct s_token_cmd		*cmd;
	int						fd[2];
	char					**cmd_array;
	struct s_instructions	*next;
}							t_instructions;

typedef struct s_token_red
{
	char				*data;
	int					type;
	char				*file;
	char				*limiter;
	struct s_token_red	*next;
}						t_token_red;

typedef struct s_token_cmd
{
	char				*data;
	int					type;
	struct s_token_cmd	*next;
}						t_token_cmd;


#endif