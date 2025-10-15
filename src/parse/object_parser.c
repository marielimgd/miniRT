/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:10:00 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/15 18:40:50 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_sphere(char **tokens, t_scene *scene, int line_number)
{
	t_object	*sphere;
	double		diameter;

	if (count_tokens(tokens) != 4)
		parse_error(line_number, "Invalid sphere parameters");
		
	sphere = create_sphere();
	sphere->origin = string_to_vector(tokens[1], 1.0);
	diameter = ft_atof(tokens[2]);
	if (diameter <= 0.0)
		parse_error(line_number, "Sphere diameter must be greater than 0");
	t_matrix *translation_m = translation(sphere->origin.x, sphere->origin.y, sphere->origin.z);
	t_matrix *scaling_m = scaling(diameter / 2.0, diameter / 2.0, diameter / 2.0);
	set_transform(sphere, matrix_product(translation_m, scaling_m));
	sphere->material.color = parse_colors(tokens[3]);
	sphere->material.ambient = 0.1;
	sphere->material.diffuse = 0.9;
	sphere->material.specular = 0.9;
	sphere->material.shininess = 200.0;
	
	ft_lstadd_back(&scene->objects, ft_lstnew(sphere));
}

void	parse_plane(char **tokens, t_scene *scene, int line_number)
{
	t_object	*plane;
	t_vector	normal;
	t_matrix	*rotation_m;
	t_matrix	*translation_m;

	if (count_tokens(tokens) != 4)
		parse_error(line_number, "Invalid plane parameters");
	plane = create_plane();
	plane->origin = string_to_vector(tokens[1], 1.0);
	normal = string_to_vector(tokens[2], 0.0);
	if (normal.x < -1.0 || normal.x > 1.0 || normal.y < -1.0
		|| normal.y > 1.0 || normal.z < -1.0 || normal.z > 1.0)
		parse_error(line_number, "Plane normal vector values must be in range [-1.0, 1.0]");
	translation_m = translation(plane->origin.x, plane->origin.y, plane->origin.z);
	rotation_m = rotation_from_orientation(normal);
	set_transform(plane, matrix_product(translation_m, rotation_m));
	plane->material.color = parse_colors(tokens[3]);
	plane->material.ambient = 0.1;
	plane->material.diffuse = 0.9;
	plane->material.specular = 0.9;
	plane->material.shininess = 200.0;
	ft_lstadd_back(&scene->objects, ft_lstnew(plane));
}

void	parse_cylinder(char **tokens, t_scene *scene, int line_number)
{
	t_object	*cylinder;
	double		diameter;
	double		height;

	if (count_tokens(tokens) != 6)
		parse_error(line_number, "Invalid cylinder parameters");

	// create a create_cylinder() constructor later and remove the following block
	cylinder = safe_malloc(sizeof(t_object), ALLOC_TYPE_OBJECT);
	if (!cylinder)
		parse_error(line_number, "Memory allocation failed for a new cylinder");
	cylinder->type = CYLINDER;

	//cylinder = create_cylinder(); //add here
	cylinder->origin = string_to_vector(tokens[1], 1.0);
	cylinder->prop.cylinder.orientation = string_to_vector(tokens[2], 0.0);
	diameter = ft_atof(tokens[3]);
	height = ft_atof(tokens[4]);
	if (diameter <= 0.0 || height <= 0.0)
		parse_error(line_number, "Cylinder diameter and height must be greater than 0");
	cylinder->prop.cylinder.diameter = diameter;
	cylinder->prop.cylinder.height = height;
	set_transform(cylinder, translation(cylinder->origin.x, cylinder->origin.y, cylinder->origin.z));
	cylinder->material.color = parse_colors(tokens[5]);
	cylinder->material.ambient = 0.1;
	cylinder->material.diffuse = 0.9;
	cylinder->material.specular = 0.9;
	cylinder->material.shininess = 200.0;
	
	ft_lstadd_back(&scene->objects, ft_lstnew(cylinder));
}
