/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_action_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:33:22 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/24 14:31:45 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

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

void	move_to_next_quote(char *sequence, int *i)
{
	char	quote;

	quote = sequence[*i];
	*i += 1;
	while (sequence[*i] && sequence[*i] != quote)
		*i += 1;
}
