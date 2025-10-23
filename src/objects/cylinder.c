/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:05:44 by jhualves          #+#    #+#             */
/*   Updated: 2025/10/23 16:05:44 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * create_cylinder
 * Allocates and initializes a cylinder object with default diameter=2 height=2
 */
t_object *create_cylinder(void)
{
	t_object *cylinder;

	cylinder = malloc(sizeof(t_object));
	if (!cylinder)
		print_error("Failed to allocate cylinder");
	cylinder->type = CYLINDER;
	cylinder->transform = identity_matrix();
	cylinder->inverse_transform = inverse_matrix(cylinder->transform);
	cylinder->transpose_inverse_transform = transpose_matrix(cylinder->inverse_transform);
	cylinder->origin = (t_vector){0, 0, 0, 1};
	cylinder->prop.cylinder.diameter = 2.0;
	cylinder->prop.cylinder.height = 2.0;
	return (cylinder);
}

/*
 * intersect_cylinder
 * Intersects a ray with a cylinder aligned with the y-axis. Cylinder in object
 * space has radius = diameter/2 and extends from -height/2 to +height/2 on y.
 */
t_intersection_list intersect_cylinder(t_object *cylinder, t_ray ray)
{
	


	
}
