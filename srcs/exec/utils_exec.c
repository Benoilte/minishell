/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:40:23 by tmartin2          #+#    #+#             */
/*   Updated: 2024/07/09 11:04:45 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	ft_get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (r);
}

int	ft_strcmp(char *s1, char *s2)
{
	while ((*s1 != '\0') || (*s2 != '\0'))
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	return (0);
}

int is_digit_only(char *str)
{
	size_t i;

	if (ft_strlen(str) == 0)
		return (1);
	i = 0;
	while (i < ft_strlen(str))
	{
		if (!ft_isdigit((unsigned char)str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	print_red_error(char *sender, t_token *red)
{
	ft_putstr_fd(sender, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (red != NULL)
		perror(red->option);
	else
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void	print_cmd_error(char *sender, t_token *cmd)
{
	ft_putstr_fd(sender, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (cmd != NULL)
		perror(cmd->data);
	else
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void	print_error_and_exit(char *sender, t_token *cmd, int status, t_bash *bash)
{
	print_cmd_error(sender, cmd);
	clear_bash_and_exit(&bash, status);
}
