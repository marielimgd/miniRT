/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:04:21 by mmariano          #+#    #+#             */
/*   Updated: 2025/08/19 15:08:59 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *str1, char *str2)
{

	if (!str1 || !str2)
		return (NULL);
	int len1 = ft_strlen(str1);
	int len2 = ft_strlen(str2);
	char *result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);

	int index1 = 0;
	while (str1[index1])
	{
		result[index1] = str1[index1];
		index1++;
	}

	int index2 = 0;
	while (str2[index2])
	{
		result[index1] = str2[index2];
		index1++;
		index2++;
	}
	result[index1] = '\0';
	return (result);
}
