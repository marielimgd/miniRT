/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:10:00 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/16 19:16:51 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_sphere(char **tokens, t_scene *scene, int line_number)
{
	t_object	*sphere;
	double		diameter;
	t_vector	position;

	if (count_tokens(tokens) != 4)
		parse_error(line_number, "Invalid sphere parameters");
	sphere = create_sphere();
	position = string_to_vector(tokens[1], 1.0);
	diameter = ft_atof(tokens[2]);
	if (diameter <= 0.0)
		parse_error(line_number, "Sphere diameter must be greater than 0");
	sphere->prop.sphere.radius = diameter / 2.0;
	set_sphere_transform(sphere, position, diameter);
	set_sphere_material(sphere, tokens[3]);
	ft_lstadd_back(&scene->objects, ft_lstnew(sphere));
	if (scene->selected_object == NULL)
		scene->selected_object = scene->objects;
}

void	parse_plane(char **tokens, t_scene *scene, int line_number)
{
	t_object	*plane;
	t_vector	normal;
	t_vector	position;

	if (count_tokens(tokens) != 4)
		parse_error(line_number, "Invalid plane parameters");
	plane = create_plane();
	position = string_to_vector(tokens[1], 1.0);
	normal = string_to_vector(tokens[2], 0.0);
	if (normal.x < -1.0 || normal.x > 1.0 || normal.y < -1.0
		|| normal.y > 1.0 || normal.z < -1.0 || normal.z > 1.0)
		parse_error(line_number,
			"Plane normal vector values must be in range [-1.0, 1.0]");
	set_plane_transform(plane, position, normal);
	set_plane_material(plane, tokens[3]);
	ft_lstadd_back(&scene->objects, ft_lstnew(plane));
	if (scene->selected_object == NULL)
		scene->selected_object = scene->objects;
}

void	init_cylinder_properties(t_object *cylinder, char **tokens,
		int line_number)
{
	double	diameter;
	double	height;

	cylinder->origin = string_to_vector(tokens[1], 1.0);
	cylinder->prop.cylinder.orientation = string_to_vector(tokens[2], 0.0);
	diameter = ft_atof(tokens[3]);
	height = ft_atof(tokens[4]);
	if (diameter <= 0.0 || height <= 0.0)
		parse_error(line_number,
			"Cylinder diameter and height must be greater than 0");
	cylinder->prop.cylinder.diameter = diameter;
	cylinder->prop.cylinder.height = height;
}

void	parse_cylinder(char **tokens, t_scene *scene, int line_number)
{
	t_object	*cylinder;

	if (count_tokens(tokens) != 6)
		parse_error(line_number, "Invalid cylinder parameters");
	cylinder = malloc(sizeof(t_object));
	if (!cylinder)
		parse_error(line_number, "Memory allocation failed for a new cylinder");
	cylinder->type = CYLINDER;
	init_cylinder_properties(cylinder, tokens, line_number);
	set_transform(cylinder, translation(cylinder->origin.x,
			cylinder->origin.y, cylinder->origin.z));
	set_cylinder_material(cylinder, tokens[5]);
	ft_lstadd_back(&scene->objects, ft_lstnew(cylinder));
	if (scene->selected_object == NULL)
		scene->selected_object = scene->objects;
}
