/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:54:53 by marieli           #+#    #+#             */
/*   Updated: 2025/10/16 16:48:01 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	calculate_orientation_vectors(t_orientation_vectors *vecs,
	t_vector from, t_vector to, t_vector up)
{
	t_vector	upn;

	subtract_tuples(&vecs->forward, &to, &from);
	normalization(&vecs->forward, &vecs->forward);
	normalization(&upn, &up);
	dot_cross(&vecs->left, &vecs->forward, &upn);
	dot_cross(&vecs->true_up, &vecs->left, &vecs->forward);
}

t_matrix	*create_orientation_matrix(t_orientation_vectors *vecs)
{
	t_matrix	*orientation;

	orientation = identity_matrix();
	orientation->matrix[0][0] = vecs->left.x;
	orientation->matrix[0][1] = vecs->left.y;
	orientation->matrix[0][2] = vecs->left.z;
	orientation->matrix[1][0] = vecs->true_up.x;
	orientation->matrix[1][1] = vecs->true_up.y;
	orientation->matrix[1][2] = vecs->true_up.z;
	orientation->matrix[2][0] = -vecs->forward.x;
	orientation->matrix[2][1] = -vecs->forward.y;
	orientation->matrix[2][2] = -vecs->forward.z;
	return (orientation);
}

t_matrix	*view_transform(t_vector from, t_vector to, t_vector up)
{
	t_orientation_vectors	vecs;
	t_matrix				*orientation;
	t_matrix				*translation_m;
	t_matrix				*view;

	calculate_orientation_vectors(&vecs, from, to, up);
	orientation = create_orientation_matrix(&vecs);
	translation_m = translation(-from.x, -from.y, -from.z);
	view = matrix_product(orientation, translation_m);
	free_matrix(orientation);
	free_matrix(translation_m);
	return (view);
}

void	camera_init(t_camera *cam, int hsize, int vsize, double fov)
{
	double	half_view;
	double	aspect;

	cam->hsize = hsize;
	cam->vsize = vsize;
	cam->fov = fov;
	half_view = tan(fov / 2.0);
	aspect = (double)hsize / (double)vsize;
	if (aspect >= 1.0)
	{
		cam->half_width = half_view;
		cam->half_height = half_view / aspect;
	}
	else
	{
		cam->half_width = half_view * aspect;
		cam->half_height = half_view;
	}
	cam->pixel_size = (cam->half_width * 2.0) / (double)hsize;
}

/*
	t_vector	pixel -> vector[0];
	t_vector	origin -> vector[1];
	t_vector	direction -> vector[2];
	double		world_x -> world[0];
	double		world_y -> world[1];
*/
t_ray	ray_for_pixel(t_camera *camera, int px, int py)
{
	t_matrix	*inv_transform;
	t_vector	vector[3];
	double		world[2];
	t_ray		ray;

	world[0] = camera->half_width - (px + 0.5) * camera->pixel_size;
	world[1] = camera->half_height - (py + 0.5) * camera->pixel_size;
	inv_transform = inverse_matrix(camera->transform);
	vector[0] = multiply_matrix_by_tuple(inv_transform,
			create_point(world[0], world[1], -1));
	vector[1] = multiply_matrix_by_tuple(inv_transform, create_point(0, 0, 0));
	subtract_tuples(&vector[2], &vector[0], &vector[1]);
	normalization(&vector[2], &vector[2]);
	ray = create_ray(vector[1], vector[2]);
	free_matrix(inv_transform);
	return (ray);
}
