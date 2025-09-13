/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:18:41 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/13 19:05:40 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* static void	setup_camera(t_camera_basis *basis, t_vector *orientation)
{
	t_vector	world_ref;
	t_vector	temp_a;

	normalization(&basis->forward, orientation);
	world_ref = create_vector(0, 1, 0);
	if (is_equal(fabs(basis->forward.y), 1.0))
		world_ref = create_vector(1, 0, 0);
	dot_cross(&temp_a, &world_ref, &basis->forward);
	normalization(&basis->right, &temp_a);
	dot_cross(&basis->up, &basis->forward, &basis->right);
}

static t_vector	combine_ray_vectors(t_camera_basis *basis,
	t_vector *cam_coords)
{
	t_vector	term1;
	t_vector	term2;
	t_vector	sum;
	t_vector	final_dir;

	scale_tuples_product(&term1, &basis->right, cam_coords->x);
	scale_tuples_product(&term2, &basis->up, cam_coords->y);
	add_tuples(&sum, &term1, &term2);
	add_tuples(&final_dir, &sum, &basis->forward);
	normalization(&final_dir, &final_dir);
	return (final_dir);
}

t_vector	calculate_ray_direction(t_camera *camera, int x, int y)
{
	t_camera_basis	basis;
	t_vector		cam_coords;
	double			aspect_ratio;

	setup_camera(&basis, &camera->direction);
	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	cam_coords.x = (2.0 * (x + 0.5) / (double)WIDTH - 1.0)
		* tan(camera->fov * 0.5 * (M_PI / 180.0)) * aspect_ratio;
	cam_coords.y = (1.0 - 2.0 * (y + 0.5) / (double)HEIGHT)
		* tan(camera->fov * 0.5 * (M_PI / 180.0));
	return (combine_ray_vectors(&basis, &cam_coords));
} */

t_ray	create_ray(t_vector origin, t_vector direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_vector	ray_position(t_ray ray, double t)
{
	t_vector	result;
	t_vector	scaled_direction;

	scale_tuples_product(&scaled_direction, &ray.direction, t);
	add_tuples(&result, &ray.origin, &scaled_direction);
	return (result);
}
