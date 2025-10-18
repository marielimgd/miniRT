/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 19:30:00 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/18 18:10:15 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_sphere_transform(t_object *sphere, t_vector position,
		double diameter)
{
	t_matrix	*translation_m;
	t_matrix	*scaling_m;

	translation_m = translation(position.x, position.y, position.z);
	scaling_m = scaling(diameter / 2.0, diameter / 2.0, diameter / 2.0);
	set_transform(sphere, matrix_product(translation_m, scaling_m));
	free_matrix(translation_m);
	free_matrix(scaling_m);
}

void	set_sphere_material(t_object *sphere, char *color_str)
{
	sphere->material.color = parse_colors(color_str);
	sphere->material.ambient = 0.1;
	sphere->material.diffuse = 0.9;
	sphere->material.specular = 0.9;
	sphere->material.shininess = 200.0;
}

void	set_plane_transform(t_object *plane, t_vector position,
		t_vector normal)
{
	t_matrix	*rotation_m;
	t_matrix	*translation_m;

	translation_m = translation(position.x, position.y, position.z);
	rotation_m = rotation_from_orientation(normal);
	set_transform(plane, matrix_product(translation_m, rotation_m));
	free_matrix(translation_m);
	free_matrix(rotation_m);
}

void	set_plane_material(t_object *plane, char *color_str)
{
	plane->material.color = parse_colors(color_str);
	plane->material.ambient = 0.1;
	plane->material.diffuse = 0.9;
	plane->material.specular = 0.9;
	plane->material.shininess = 200.0;
}

void	set_cylinder_material(t_object *cylinder, char *color_str)
{
	cylinder->material.color = parse_colors(color_str);
	cylinder->material.ambient = 0.1;
	cylinder->material.diffuse = 0.9;
	cylinder->material.specular = 0.9;
	cylinder->material.shininess = 200.0;
}
//ADD NO .H
void	set_cylinder_transform(t_object *cylinder, t_vector origin, \
	t_vector orientation, double diameter, double height)
{
	t_matrix	*translation_m;
	t_matrix	*rotation_m;
	t_matrix	*scaling_m;
	t_matrix	*rot_scale;
	t_matrix	*transform;
	
	rotation_m = set_cylinder_transform_utils(rotation_m, &orientation);
	translation_m = translation(origin.x, origin.y, origin.z);
	scaling_m = scaling(diameter / 2.0, height / 2.0, diameter / 2.0);
	rot_scale = matrix_product(rotation_m, scaling_m);
	transform = matrix_product(translation_m, rot_scale);
	set_transform(cylinder, transform);
	free_matrix(translation_m);
	free_matrix(rotation_m);
	free_matrix(scaling_m);
	free_matrix(rot_scale);
}

t_matrix	*set_cylinder_transform_utils(t_matrix *rotation_m, \
	t_vector *orientation)
{
	t_vector norm;
	
	normalization(&norm, orientation);
	rotation_m = rotation_from_orientation(norm);
	return (rotation_m);
}
