/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_action_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:33:22 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/18 08:34:38 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	move_to_next_quote(char *sequence, int *i)
{
	char	quote;

	quote = sequence[*i];
	*i += 1;
	while (sequence[*i] && sequence[*i] != quote)
		*i += 1;
}
