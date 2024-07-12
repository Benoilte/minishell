/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_interactive_minishell.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:56:33 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/12 09:23:24 by bebrandt         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void	start_non_interactive_minishell(t_bash *bash, char *file, int debug)
{
	bash->fd_arg_file = open_arg_file(file);
	if (bash->fd_arg_file == -1)
		return ;
	if (is_wrong_file_format(file, bash->fd_arg_file))
	{
		close(bash->fd_arg_file);
		return ;
	}
	else
	{
		while (1)
		{
			bash->sequence = get_sequence(bash->fd_arg_file);
			if (!bash->sequence)
				break ;
			check_sequence_and_execution(bash, debug);
			clear_instruction(&(bash)->instruction);
			free(bash->sequence);
			bash->sequence = NULL;
		}
	}
	close(bash->fd_arg_file);
	bash->fd_arg_file = -1;
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
		free(first_line);
	else
	{
		free(first_line);
		ft_printf("%s: file should start with `#! minishell`\n", file);
		return (1);
	}
	return (0);
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

int	open_arg_file(char *arg_file)
{
	int	fd;

	fd = open(arg_file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(arg_file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	return (fd);
}
