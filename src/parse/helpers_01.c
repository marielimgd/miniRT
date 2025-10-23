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
	t_matrix	*translation_m -> t_matrix *matrices[0];
	t_matrix	*rotation_m -> t_matrix *matrices[1];
	t_matrix	*transform_m -> t_matrix *matrices[2];
*/
void	set_cylinder_transform(t_object *cylinder, t_vector origin, \
t_vector orientation)
{
	t_matrix	*matrices[3];
	t_matrix	*scale[2];
	double		diameter;
	double		height;

	diameter = cylinder->prop.cylinder.diameter;
	height = cylinder->prop.cylinder.height;
	matrices[1] = NULL;
	matrices[1] = set_cylinder_transform_utils(matrices[1], &orientation);
	matrices[0] = translation(origin.x, origin.y, origin.z);
	scale[0] = scaling(diameter / 2.0, height / 2.0, diameter / 2.0);
	scale[1] = matrix_product(matrices[1], scale[0]);
	matrices[2] = matrix_product(matrices[0], scale[1]);
	set_transform(cylinder, matrices[2]);
	free_matrix(matrices[0]);
	free_matrix(matrices[1]);
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
