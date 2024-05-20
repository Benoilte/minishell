/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:33:22 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/20 00:05:39 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

/*
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options
*/

int	is_builtin(char *word)
{
	if (ft_strlen(word) == 0)
		return (0);
	if (ft_strncmp(word, "echo", ft_strlen(word)) == 0)
		return (1);
	if (ft_strncmp(word, "cd", ft_strlen(word)) == 0)
		return (1);
	if (ft_strncmp(word, "pwd", ft_strlen(word)) == 0)
		return (1);
	if (ft_strncmp(word, "export", ft_strlen(word)) == 0)
		return (1);
	if (ft_strncmp(word, "unset", ft_strlen(word)) == 0)
		return (1);
	if (ft_strncmp(word, "env", ft_strlen(word)) == 0)
		return (1);
	if (ft_strncmp(word, "exit", ft_strlen(word)) == 0)
		return (1);
	return (0);
}

int	is_unexpected_token_cmd(char c)
{
	char	*tokens;
	int		i;

	tokens = "();&";
	i = 0;
	while (tokens[i])
	{
		if (tokens[i] == c)
			return (1);
		i++;
	}
	return (0);
}
