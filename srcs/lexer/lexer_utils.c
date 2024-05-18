/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:33:22 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/18 12:06:06 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	define_cmd_token_type(t_token *token, int *cmd, char quote)
{
	if (quote == '\'')
		token->data_type |= S_QUOTES;
	if (quote == '\"')
		token->data_type |= D_QUOTES;
	if (*cmd == 0)
	{
		if (is_builtin(token->data))
			token->data_type |= BUILTIN;
		else
			token->data_type |= CMD;
	}
	else
		token->data_type |= WORD;
	*cmd += 1;
}

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
