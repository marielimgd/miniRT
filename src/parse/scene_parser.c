/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:42:09 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/15 17:32:33 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector string_to_vector(char *str, double w)
{
	t_vector 	vector;
	char 		**values;

	values = ft_split(str, ',');
	if (!values)
		parse_error(0, "Invalid vector format. Expected: x, y, z\n");
	if (count_tokens(values) != 3)
	{
		free_tokens(values);
		parse_error(0, "Invalid vector format. Expected: x, y, z\n");
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
	t_vector	to;
	int 		fov;


	if (scene->has_camera)
		parse_error(line_number, "Camera already defined in the scene");
	if (count_tokens(tokens) != 4)
		parse_error(line_number, "Invalid camera parameters");
	scene->has_camera = true;
	scene->camera.from = string_to_vector(tokens[1], 1.0);
	scene->camera.orientation = string_to_vector(tokens[2], 0.0);
	scene->camera.up = create_vector(0, 1, 0);
	fov = ft_atoi(tokens[3]);
	if (scene->camera.orientation.x < -1.0 || scene->camera.orientation.x > 1.0 || scene->camera.orientation.y < -1.0
		|| scene->camera.orientation.y > 1.0 || scene->camera.orientation.z < -1.0 || scene->camera.orientation.z > 1.0)
		parse_error(line_number, "Camera orientation vector values out of range [-1.0, 1.0]");
	if (fov < 0 || fov > 180)
		parse_error(line_number, "Camera FOV must be between 0 and 180 degrees");
	camera_init(&scene->camera, WIDTH, HEIGHT, fov * (M_PI / 180.0));
	add_tuples(&to, &scene->camera.from, &scene->camera.orientation);
	scene->camera.transform = view_transform(scene->camera.from, to,
			scene->camera.up);
}

void 	parse_ambient_light(char**tokens, t_scene *scene, int line_number)
{
	double	ratio;
	
	if(count_tokens(tokens) != 3)
		parse_error(line_number, "Invalid ambient light parameters");
	if (scene->has_ambient)
		parse_error(line_number, "Ambient light already defined in the scene");
	
	ratio = ft_atof(tokens[1]);
	if (ratio < 0.0 || ratio > 1.0)
		parse_error(line_number, "Ambient light ratio is out of range (0.0 to 1.0)");
	
	scene->has_ambient = true;
	scene->ambient_light = ratio;
	scene->ambient_color = parse_colors(tokens[2]);
}

void 	parse_light(char**tokens, t_scene *scene, int line_number)
{
	t_light *light;
	double brightness;

	if(count_tokens(tokens) != 4)
		parse_error(line_number, "Invalid light parameters");

	light = malloc(sizeof(t_light));
	if (!light)
		parse_error(line_number, "Memory allocation failed for light");
	
	light->origin = string_to_vector(tokens[1], 1.0);
	brightness = ft_atof(tokens[2]);
	if (brightness < 0.0 || brightness > 1.0)
	{
		free(light);
		parse_error(line_number, "Light brightness is out of range (0.0 to 1.0)");
	}
	light->brightness = brightness;
	
	light->color = parse_colors(tokens[3]);
	ft_lstadd_back(&scene->lights, ft_lstnew(light));//add more than one light
}
