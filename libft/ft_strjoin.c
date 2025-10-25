/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:04:21 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/25 15:16:26 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		size;
	char	*s3;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1);
	size += ft_strlen(s2);
	s3 = malloc(size + 1);
	result = s3;
	while (*s1)
		*s3++ = *s1++;
	while (*s2)
		*s3++ = *s2++;
	*s3 = '\0';
	return (result);
}
