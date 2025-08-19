/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:21:02 by marielidias       #+#    #+#             */
/*   Updated: 2025/08/19 15:16:11 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	index;
	size_t	str_len;
	char	*str;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_strdup(""));
	if (len > str_len - start)
		len = str_len - start;
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	index = 0;
	while (index < len)
	{
		str[index] = s[start + index];
		index++;
	}
	return (str);
}
