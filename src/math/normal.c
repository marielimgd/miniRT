/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:16:02 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/11 19:25:25 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	normal_at(t_object *object, t_vector world_point)
{
	if (object->type == SPHERE)
		return (normal_at_sphere(object, world_point));
	// else if (object->type == PLANE)
	// 	return (normal_at_plane(object, world_point));
	// else if (object->type == CYLINDER)
	// 	return (normal_at_cylinder(object, world_point));
	
	return (create_vector(0, 0, 0));
}
