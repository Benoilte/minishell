/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_interactive_minishell.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:56:33 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/17 16:29:05 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	start_non_interactive_minishell(t_bash *bash, char *file, int debug)
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
			check_sequence_and_execution(bash, debug);
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
