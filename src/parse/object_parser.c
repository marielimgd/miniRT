/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:10:00 by mmariano          #+#    #+#             */
/*   Updated: 2025/08/19 13:14:06 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "parser.h"
#include "libft.h"

void 	parse_sphere(char**tokens, t_scene *scene)
{
	t_object    *sphere;
    double      diameter;

    if (count_tokens(tokens) != 4)
        parse_error("Invalid sphere parameters");

    sphere = malloc(sizeof(t_object));
    if (!sphere)
        parse_error("Memory allocation failed for a new sphere");
    sphere->type = SPHERE;

    sphere->origin = string_to_vector(tokens[1]);
    diameter = ft_atof(tokens[2]);
    sphere->color = parse_colors(tokens[3]);
    
    if (diameter <= 0.0)
    {
        free(sphere);
        parse_error("Sphere diameter must be greater than 0");
    }
    sphere->diameter = diameter;
    ft_lstadd_back(&scene->objects, ft_lstnew(sphere)); //new sphere
}

void 	parse_cylinder(char**tokens, t_scene *scene)
{
    t_object    *cylinder;
    double      diameter;
    double      height;

    if (count_tokens(tokens) != 6)
        parse_error("Invalid cylinder parameters");

    cylinder = malloc(sizeof(t_object));
    if (!cylinder)
        parse_error("Memory allocation failed for a new cylinder");
    cylinder->type = CYLINDER;

    cylinder->origin = string_to_vector(tokens[1]);
	cylinder->cylinder.orientation = string_to_vector(tokens[2]);
    cylinder->color = parse_colors(tokens[5]);
    if (diameter <= 0.0 || height <= 0.0)
    {
        free(cylinder);
        parse_error("Cylinder diameter and height must be greater than 0");
    }
	diameter = ft_atof(tokens[3]);
    cylinder->cylinder.diameter = diameter;
	height = ft_atof(tokens[4]);
    cylinder->cylinder.height = height;
    ft_lstadd_back(&scene->objects, ft_lstnew(cylinder)); //new cylinder
}
