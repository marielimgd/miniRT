/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 19:30:00 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/22 21:52:14 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
