/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_action_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:33:22 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/01 15:06:58 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	is_builtin(char *word)
{
	if (ft_strlen(word) == 0)
		return (0);
	if (ft_my_strcmp(word, "echo") == 0)
		return (1);
	if (ft_my_strcmp(word, "cd") == 0)
		return (1);
	if (ft_my_strcmp(word, "pwd") == 0)
		return (1);
	if (ft_my_strcmp(word, "export") == 0)
		return (1);
	if (ft_my_strcmp(word, "unset") == 0)
		return (1);
	if (ft_my_strcmp(word, "env") == 0)
		return (1);
	if (ft_my_strcmp(word, "exit") == 0)
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
