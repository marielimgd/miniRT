/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:42:09 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/23 11:05:51 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minirt.h"

t_vector	string_to_vector(char *str, double w)
{
	t_vector	vector;
	char		**values;

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

static void	validate_camera_orientation(t_scene *scene, int line_number)
{
	if (scene->camera.orientation.x < -1.0
		|| scene->camera.orientation.x > 1.0
		|| scene->camera.orientation.y < -1.0
		|| scene->camera.orientation.y > 1.0
		|| scene->camera.orientation.z < -1.0
		|| scene->camera.orientation.z > 1.0)
		parse_error(line_number,
			"Camera orientation vector values out of range [-1.0, 1.0]");
}

static void	setup_camera_transform(t_scene *scene)
{
	t_vector	to;

	add_tuples(&to, &scene->camera.from, &scene->camera.orientation);
	scene->camera.transform = view_transform(scene->camera.from, to,
			scene->camera.up);
}

void	parse_camera(char **tokens, t_scene *scene, int line_number)
{
	int	fov;

	if (scene->has_camera)
		parse_error(line_number, "Camera already defined in the scene");
	if (count_tokens(tokens) != 4)
		parse_error(line_number, "Invalid camera parameters");
	scene->has_camera = true;
	scene->camera.from = string_to_vector(tokens[1], 1.0);
	scene->camera.orientation = string_to_vector(tokens[2], 0.0);
	if (fabs(scene->camera.orientation.y) > 0.999)
		scene->camera.up = create_vector(0, 0, 1);
	else
		scene->camera.up = create_vector(0, 1, 0);
	fov = ft_atoi(tokens[3]);
	validate_camera_orientation(scene, line_number);
	if (fov < 0 || fov > 180)
		parse_error(line_number, \
"Camera FOV must be between 0 and 180 degrees");
	camera_init(&scene->camera, WIDTH, HEIGHT, fov * (M_PI / 180.0));
	setup_camera_transform(scene);
}
