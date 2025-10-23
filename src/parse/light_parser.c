/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:36:22 by jhualves          #+#    #+#             */
/*   Updated: 2025/10/23 15:36:22 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambient_light(char **tokens, t_scene *scene, int line_number)
{
	double	ratio;

	if (count_tokens(tokens) != 3)
		parse_error(line_number, "Invalid ambient light parameters");
	if (scene->has_ambient)
		parse_error(line_number,
			"Ambient light already defined in the scene");
	ratio = ft_atof(tokens[1]);
	if (ratio < 0.0 || ratio > 1.0)
		parse_error(line_number,
			"Ambient light ratio is out of range (0.0 to 1.0)");
	scene->has_ambient = true;
	scene->ambient_light = ratio;
	scene->ambient_color = parse_colors(tokens[2]);
}

void	parse_light(char **tokens, t_scene *scene, int line_number)
{
	t_light		*light;
	double		brightness;

	if (count_tokens(tokens) != 4)
		parse_error(line_number, "Invalid light parameters");
	light = malloc(sizeof(t_light));
	if (!light)
		parse_error(line_number, "Memory allocation failed for light");
	light->origin = string_to_vector(tokens[1], 1.0);
	brightness = ft_atof(tokens[2]);
	if (brightness < 0.0 || brightness > 1.0)
	{
		free(light);
		parse_error(line_number,
			"Light brightness is out of range (0.0 to 1.0)");
	}
	light->brightness = brightness;
	light->color = parse_colors(tokens[3]);
	ft_lstadd_back(&scene->lights, ft_lstnew(light));
}
