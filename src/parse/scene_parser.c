/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:42:09 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/15 18:58:11 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector string_to_vector(char *str, double w)
{
	t_vector 	vector;
	char 		**values;
	int			line_number;

	values = ft_split(str, ',');
	if (!values)
		parse_error("Invalid vector format. Expected: x, y, z\n", line_number);
	if (count_tokens(values) != 3)
	{
		free_tokens(values);
		parse_error("Invalid vector format. Expected: x, y, z\n", line_number);
	}
	vector.x = ft_atof(values[0]);
	vector.y = ft_atof(values[1]);
	vector.z = ft_atof(values[2]);
	vector.w = w;
	free_tokens(values);
	return (vector);
}

void	parse_camera(char **tokens, t_scene *scene, int line_number)
{
	t_vector	from;
	t_vector	to;
	t_vector	orientation;
	t_vector	up;
	int			fov;

	if (scene->has_camera)
		parse_error(line_number, "Camera already defined in the scene");
	if (count_tokens(tokens) != 4)
		parse_error("Invalid camera parameters", line_number);
	from = string_to_vector(tokens[1], 1.0);
	orientation = string_to_vector(tokens[2], 0.0);
	fov = ft_atoi(tokens[3]);
	if (orientation.x < -1.0 || orientation.x > 1.0 || orientation.y < -1.0
		|| orientation.y > 1.0 || orientation.z < -1.0 || orientation.z > 1.0)
		parse_error("Camera orientation vector values out of range [-1.0, 1.0]", line_number);
	if (fov < 0 || fov > 180)
		parse_error("Camera FOV must be between 0 and 180 degrees", line_number);
	camera_init(&scene->camera, WIDTH, HEIGHT, fov * (M_PI / 180.0));
	add_tuples(&to, &from, &orientation);
	up = create_vector(0, 1, 0);
	scene->camera.transform = view_transform(from, to, up);
}

void 	parse_ambient_light(char**tokens, t_scene *scene, int line_number)
{
	double	ratio;
	
	if(count_tokens(tokens) != 3)
		parse_error("Invalid ambient light parameters", line_number);
	if (scene->has_ambient)
		parse_error("Ambient light already defined in the scene", line_number);
	
	ratio = ft_atof(tokens[1]);
	if (ratio < 0.0 || ratio > 1.0)
		parse_error("Ambient light ratio is out of range (0.0 to 1.0)", line_number);
	
	scene->has_ambient = true;
	scene->ambient_light = ratio;
	scene->ambient_color = parse_colors(tokens[2]);
}

void 	parse_light(char**tokens, t_scene *scene, int line_number)
{
	t_light *light;
	double brightness;

	if(count_tokens(tokens) != 4)
		parse_error("Invalid light parameters", line_number);

	light = malloc(sizeof(t_light));
	if (!light)
		parse_error("Memory allocation failed for light", line_number);
	
	light->origin = string_to_vector(tokens[1], 1.0);
	brightness = ft_atof(tokens[2]);
	if (brightness < 0.0 || brightness > 1.0)
	{
		free(light);
		parse_error("Light brightness is out of range (0.0 to 1.0)", line_number);
	}
	light->brightness = brightness;
	
	light->color = parse_colors(tokens[3]);
	ft_lstadd_back(&scene->lights, ft_lstnew(light));//add more than one light
}
