/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_interactive_minishell.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:56:33 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/08 17:54:43 by bebrandt         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void	start_non_interactive_minishell(t_bash *bash, char *file, int debug)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("open()");
		return ;
	}
	if (is_wrong_file_format(file, fd))
	{
		close (fd);
		return ;
	}
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

int	is_wrong_file_format(char *file, int fd)
{
	char	*extension;
	char	*first_line;

	extension = ft_strrchr(file, '.');
	if (ft_my_strcmp(extension, ".sh") != 0)
	{
		ft_printf("%s: extension file should be `.sh`\n", file);
		return (1);
	}
	first_line = get_next_line(fd);
	if (!first_line)
	{
		ft_printf("%s: file is empty\n", file);
		return (1);
	}
	if (ft_my_strcmp(first_line, "#! minishell\n") == 0
		|| ft_my_strcmp(first_line, "#! minishell") == 0)
		return (0);
	else
	{
		free(first_line);
		ft_printf("%s: file should start with `#! minishell`\n", file);
		return (1);
	}
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
