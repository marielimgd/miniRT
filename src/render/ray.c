/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:18:41 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/08 18:03:09 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	setup_camera(t_vector *forward, t_vector *right, t_vector *up)
{
	t_vector	world_ref;
	t_vector	*temp_a;
	t_vector	*temp_b;

	world_ref.x = 0;
	world_ref.y = 1;
	world_ref.z = 0;
	world_ref.w = 0;
	if (is_equal(fabs(forward->y), 1.0)) //if he camera is totally up or down
	{
		world_ref.x = 1;
		world_ref.y = 0;
	}
	temp_a = dot_cross(&world_ref, forward);
	temp_b = normalization(temp_a);
	*right = *temp_b;
	free(temp_a);
	free(temp_b);
	temp_a = dot_cross(forward, right);
	*up = *temp_a;
	free(temp_a);
}
static t_vector	*combine_ray_vectors(t_vector *right, t_vector *up, t_vector *forward, t_vector *cam_coords)
{
	t_vector	*term1;
	t_vector	*term2;
	t_vector	*sum;
	t_vector	*final_dir;

	term1 = scale_tuples_product(right, cam_coords->x);
	term2 = scale_tuples_product(up, cam_coords->y);
	sum = add_tuples(term1, term2);
	final_dir = add_tuples(sum, forward);
	free(term1);
	free(term2);
	free(sum);
	sum = normalization(final_dir);
	free(final_dir);
	return (sum);
}

t_vector	calculate_ray_direction(t_camera *camera, int x, int y)
{
	t_vector	right;
	t_vector	up;
	t_vector	forward;
	t_vector	cam_coords;
	t_vector	*final_dir;

	//camera direction
	final_dir = normalization(&(camera->orientation));
	forward = *final_dir;
	free(final_dir);
	setup_camera(&forward, &right, &up);

	//convert pixel coordinates to fit in the plane
	cam_coords.x = (2.0 * (x + 0.5) / (double)WIDTH - 1.0) * tan(camera->fov * 0.5 * (M_PI / 180.0));
	cam_coords.y = (1.0 - 2.0 * (y + 0.5) / (double)HEIGHT) * tan(camera->fov * 0.5 * (M_PI / 180.0)) / ((double)WIDTH / (double)HEIGHT);
	
	//final ray direction
	final_dir = combine_ray_vectors(&right, &up, &forward, &cam_coords);
	right = *final_dir;
	free(final_dir);
	return (right);
}

t_ray create_ray(t_vector origin, t_vector direction)
{
	t_ray ray;
	
	ray.origin = origin;
	ray.direction = direction;
	
	return(ray);
}
//formula: position = origin + direction * t
t_vector ray_position(t_ray ray, double t)
{
	t_vector	result;
	t_vector	*scaled_direction;
	t_vector	*new_position;

	scaled_direction = scale_tuples_product(&ray.direction, t);
	new_position = add_tuples(&ray.origin, scaled_direction);
	result = *new_position;
	free(scaled_direction);
	free(new_position);
	return (result);
}
