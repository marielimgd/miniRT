/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:35:29 by jhualves          #+#    #+#             */
/*   Updated: 2025/10/23 15:35:29 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
/ 	t_matrix	*scaling_m -> t_matrix *scale[0];
	t_matrix	*rot_scale -> t_matrix *scale[1];
*/
void	set_cylinder_transform(t_object *cylinder, t_vector origin, \
t_vector orientation, double diameter, double height)
{
	t_matrix	*translation_m;
	t_matrix	*rotation_m;
	t_matrix	*transform;
	t_matrix	*scale[2];

	rotation_m = NULL;
	rotation_m = set_cylinder_transform_utils(rotation_m, &orientation);
	translation_m = translation(origin.x, origin.y, origin.z);
	scale[0] = scaling(diameter / 2.0, height / 2.0, diameter / 2.0);
	scale[1] = matrix_product(rotation_m, scale[0]);
	transform = matrix_product(translation_m, scale[1]);
	set_transform(cylinder, transform);
	free_matrix(translation_m);
	free_matrix(rotation_m);
	free_matrix(scale[0]);
	free_matrix(scale[1]);
}

t_matrix	*set_cylinder_transform_utils(t_matrix *rotation_m, \
t_vector *orientation)
{
	t_vector	norm;

	normalization(&norm, orientation);
	rotation_m = rotation_from_orientation(norm);
	return (rotation_m);
}
