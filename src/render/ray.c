/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:18:41 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/12 21:54:35 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

static void	calculate_pixel_and_origin(t_vector *pixel, t_vector *origin,
	t_camera *camera, int px, int py)
{
	t_matrix	*inv_transform;
	double		world_x;
	double		world_y;

	world_x = camera->half_width - (px + 0.5) * camera->pixel_size;
	world_y = camera->half_height - (py + 0.5) * camera->pixel_size;
	inv_transform = inverse_matrix(camera->transform);
	*pixel = multiply_matrix_by_tuple(inv_transform,
			create_point(world_x, world_y, -1));
	*origin = multiply_matrix_by_tuple(inv_transform,
			create_point(0, 0, 0));
	free_matrix(inv_transform);
}

t_ray	ray_for_pixel(t_camera *camera, int px, int py)
{
	t_vector	pixel;
	t_vector	origin;
	t_vector	direction;
	
	calculate_pixel_and_origin(&pixel, &origin, camera, px, py);
	subtract_tuples(&direction, &pixel, &origin);
	normalization(&direction, &direction);
	return (create_ray(origin, direction));
}
