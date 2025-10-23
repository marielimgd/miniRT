/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 19:30:00 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/22 22:11:38 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minirt.h"

/*
/ refatorar essa função
*/
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
	t_vector	norm;

	normalization(&norm, orientation);
	rotation_m = rotation_from_orientation(norm);
	return (rotation_m);
}
