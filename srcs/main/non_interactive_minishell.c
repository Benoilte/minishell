/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_interactive_minishell.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:56:33 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/10 16:32:35 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	start_non_interactive_minishell(t_bash *bash, char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror("open()");
	else
	{
		while (1)
		{
			bash->sequence = get_sequence(fd);
			if (!bash->sequence)
				break ;
			if (lexing(bash, bash->sequence) == RETURN_SUCCESS)
			{
				if (parsing(bash) == PARSING_OK)
				{
					test_print_instruction(bash->instruction);
				}
			}
			clear_instruction(&(bash)->instruction);
			free(bash->sequence);
			bash->sequence = NULL;
		}
	}
	close(fd);
}

char	*get_sequence(int fd)
{
	char	*line;
	char	*sequence;
	int		i;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '#')
	{
		free(line);
		return (ft_strdup(""));
	}
	if (ft_strchr(line, '\n'))
	{
		sequence = ft_substr(line, i, (ft_strlen(line + i) - 1));
		free(line);
		return (sequence);
	}
	return (line);
}
