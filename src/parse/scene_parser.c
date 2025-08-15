/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:42:09 by mmariano          #+#    #+#             */
/*   Updated: 2025/08/14 21:03:53 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "scene.h"

t_vector string_to_vector(char *str)
{
	t_vector 	vector;
	char 		**values;

	values = ft_split(str, ',');
	if (!values)
		parse_error("Invalid vector format. Expected: x, y, z\n");
	if (ft_strarrlen(values) != 3)
	{
		free_tokens(values);
		parse_error("Invalid vector format. Expected: x, y, z\n");
	}
	vector.x = ft_atof(values[0]);
	vector.y = ft_atof(values[1]);
	vector.z = ft_atof(values[2]);
	free_tokens(values);
	return (vector);
}

void 	parse_camera(char**tokens, t_scene *scene)
{
	t_vector	orientation;
	int 		fov;

	if(count_tokens(tokens) != 4)
		parse_error("Invalid camera parameters");

	scene->camera.origin = string_to_vector(tokens[1]);
	
	orientation = string_to_vector(tokens[2]);
	if (orientation.x < -1.0 || orientation.x > 1.0 ||
		orientation.y < -1.0 || orientation.y > 1.0 ||
		orientation.z < -1.0 || orientation.z > 1.0)
		parse_error("Camera orientation vector values is out of range (-1.0 to 1.0)\n");

	fov = ft_atoi(tokens[3]);
	if (fov < 0 || fov > 180)
		parse_error("Camera FOV must be between 0 and 180 degrees\n");
	
	scene->camera.direction = orientation;
	scene->camera.fov = fov;	
}

void 	parse_ambient_light(char**tokens, t_scene *scene)
{
	if(count_tokens(tokens) != 3)
		parse_error("Invalid ambient light parameters");

	scene->ambient_light = ft_atof(tokens[1]);
	scene->ambient_color = parse_colors(tokens[2]);
	if (scene->ambient_light < 0.0 || scene->ambient_light > 1.0)
		parse_error("Ambient light ratio is out of range (0.0 to 1.0)\n");
}

void 	parse_light(char**tokens, t_scene *scene)
{
	if(count_tokens(tokens) != 3)
		parse_error("Invalid light parameters");

	
}