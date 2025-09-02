/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:08:15 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/02 16:42:25 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	validate_rgb_values(char **rgb_values)
{
	int	index;
	int	j;
	int	value;

	index = 0;
	while (index < 3)
	{
		j = 0;
		while (rgb_values[index][j])
		{
			if (!ft_isdigit(rgb_values[index][j]) && rgb_values[index][j] != '-'
				&& rgb_values[index][j] != '+')
				parse_error("Color values must be numeric\n");
			j++;
		}
		value = ft_atoi(rgb_values[index]);
		if (value < 0 || value > 255)
			parse_error("Invalid color value\n");
		index++;
	}
}

t_color	parse_colors(char *str)
{
	t_color color;
	char **rgb_values;

	rgb_values = ft_split(str, ',');
	if (!rgb_values || !rgb_values[0] || !rgb_values[1] || !rgb_values[2])
		parse_error("Memory allocation failed during color parsing\n");
	validate_rgb_values(rgb_values);
	color.r = ft_atoi(rgb_values[0]);
	color.g = ft_atoi(rgb_values[1]);
	color.b = ft_atoi(rgb_values[2]);
	free_tokens(rgb_values);
	return (color);
}
