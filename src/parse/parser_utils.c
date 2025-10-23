/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:15:50 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/22 22:12:58 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minirt.h"

void	parse_error(int line_number, char *message)
{
	ft_putstr_fd("Parse error on line ", 2);
	ft_putnbr_fd(line_number, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	free_tokens(char **tokens)
{
	int index;

	index = 0;
	if (!tokens)
		return;
	while (tokens[index])
	{
		free(tokens[index]);
		index++;
	}
	free(tokens);
}
int count_tokens(char **tokens)
{
	int index;

	index = 0;
	if (!tokens || !*tokens)
		return (0);
	while (tokens[index])
		index++;
	return (index);
}
