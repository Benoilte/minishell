/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_strcmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:04:06 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/01 13:08:28 by bebrandt         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/libft.h"

/*
Compare two string.
return 0 if they are the same or the 'chars' difference of s1 - s2
*/
int	ft_my_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((int)(unsigned char)s1[i] - (int)(unsigned char)s2[i]);
}
