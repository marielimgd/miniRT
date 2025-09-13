/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:10:00 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/12 21:29:13 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void init_sphere(t_object *sphere, double diameter)
{
    sphere->prop.sphere.radius = diameter / 2.0;
	sphere->material.color = sphere->color;
	sphere->material.ambient = 0.1;
	sphere->material.diffuse = 0.9;
	sphere->material.specular = 0.9;
	sphere->material.shininess = 200.0;
	sphere->transform = identity_matrix();
	sphere->inverse_transform = inverse_matrix(sphere->transform);
	sphere->transpose_inverse_transform = transpose_matrix(sphere->inverse_transform);

}

void	parse_sphere(char **tokens, t_scene *scene)
{
	t_object	*sphere;
	double		diameter;

	if (count_tokens(tokens) != 4)
		parse_error("Invalid sphere parameters");
	sphere = safe_malloc(sizeof(t_object), ALLOC_TYPE_OBJECT);
	if (!sphere)
		parse_error("Memory allocation failed for a new sphere");
	sphere->type = SPHERE;
	sphere->origin = string_to_vector(tokens[1], 1.0);
	diameter = ft_atof(tokens[2]);
	sphere->color = parse_colors(tokens[3]);
	if (diameter <= 0.0)
	{
		free(sphere);
		parse_error("Sphere diameter must be greater than 0");
	}
    init_sphere(sphere, diameter);
    ft_lstadd_back(&scene->objects, ft_lstnew(sphere));
}

void parse_plane(char **tokens, t_scene *scene)
{
    t_object    *plane;
    t_vector    normal;

    if (count_tokens(tokens) != 4)
        parse_error("Invalid plane parameters");
    plane = safe_malloc(sizeof(t_object), ALLOC_TYPE_GENERIC);
    if (!plane)
        parse_error("Memory allocation failed for a new plane");
    plane->type = PLANE;
    plane->origin = string_to_vector(tokens[1], 1.0);
    normal = string_to_vector(tokens[2], 0.0);
    plane->color = parse_colors(tokens[3]);
    if (normal.x < -1.0 || normal.x > 1.0 ||
        normal.y < -1.0 || normal.y > 1.0 ||
        normal.z < -1.0 || normal.z > 1.0)
    {
        free(plane);
        parse_error("Plane normal vector values must be in range [-1.0, 1.0]");
    }
    plane->prop.plane.normal = normal;
    ft_lstadd_back(&scene->objects, ft_lstnew(plane));
    
}

void 	parse_cylinder(char**tokens, t_scene *scene)
{
    t_object    *cylinder;
    double      diameter;
    double      height;

    if (count_tokens(tokens) != 6)
        parse_error("Invalid cylinder parameters");

    cylinder = safe_malloc(sizeof(t_object), ALLOC_TYPE_GENERIC);
    if (!cylinder)
        parse_error("Memory allocation failed for a new cylinder");
    cylinder->type = CYLINDER;

    cylinder->origin = string_to_vector(tokens[1], 1.0);
	cylinder->prop.cylinder.orientation = string_to_vector(tokens[2], 0.0);
    diameter = ft_atof(tokens[3]);
	height = ft_atof(tokens[4]);
    cylinder->color = parse_colors(tokens[5]);
    if (diameter <= 0.0 || height <= 0.0)
    {
        free(cylinder);
        parse_error("Cylinder diameter and height must be greater than 0");
    }
    cylinder->prop.cylinder.diameter = diameter;
    cylinder->prop.cylinder.height = height;
    ft_lstadd_back(&scene->objects, ft_lstnew(cylinder));
}
