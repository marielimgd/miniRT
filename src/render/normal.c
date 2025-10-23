/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:16:02 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/16 18:32:40 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	normal_at_sphere(t_object *sphere, t_vector world_point)
{
	t_vector	object_point;
	t_vector	object_normal;
	t_vector	world_normal;

	object_point = multiply_matrix_by_tuple(sphere->inverse_transform,
			world_point);
	subtract_tuples(&object_normal, &object_point, &sphere->origin);
	world_normal = multiply_matrix_by_tuple(
			sphere->transpose_inverse_transform, object_normal);
	world_normal.w = 0;

	normalization(&world_normal, &world_normal);
	return (world_normal);
}

t_vector	normal_at_plane(t_object *plane, t_vector world_point)
{
	t_vector	object_normal;
	t_vector	world_normal;

	(void)world_point;
	object_normal = create_vector(0, 1, 0);
	world_normal = multiply_matrix_by_tuple(plane->transpose_inverse_transform,
			object_normal);
	world_normal.w = 0;

	normalization(&world_normal, &world_normal);
	return (world_normal);
}

t_vector	normal_at(t_object *object, t_vector world_point)
{
	if (object->type == SPHERE)
		return (normal_at_sphere(object, world_point));
	else if (object->type == PLANE)
		return (normal_at_plane(object, world_point));
	// else if (object->type == CYLINDER)
	// 	return (normal_at_cylinder(object, world_point));

	return (create_vector(0, 0, 0));
}
