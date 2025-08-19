/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:15:50 by mmariano          #+#    #+#             */
/*   Updated: 2025/08/19 13:27:00 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "parser.h"

void parse_error(char *message)
{
	ft_putstr_fd("Parse error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void free_tokens(char **tokens)
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
