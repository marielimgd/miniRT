/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:18:41 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/02 19:51:47 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//MATH functions:
t_vector	add_vectors(t_vector a, t_vector b);
t_vector	multiply_scalar(t_vector vector, double scalar);
t_vector	vector_normalize(t_vector v);
t_vector	vector_cross_product(t_vector a, t_vector b);

static void	setup_camera_basis(t_vector forward, t_vector *right, t_vector *up)
{
	t_vector	world_ref;

	world_ref.x = 0;
	world_ref.y = 1;
	world_ref.z = 0;
	world_ref.w = 0;

	//if he camera is totally up or down
	if (fabs(forward.y) == 1.0)
	{
		world_ref.x = 1;
		world_ref.y = 0;
	}
	*right = vector_normalize(vector_cross_product(world_ref, forward));
	*up = vector_cross_product(forward, *right);
}


t_vector	calculate_ray_direction(t_camera *camera, int x, int y)
{
	t_vector 	right;
	t_vector 	up;
	t_vector 	forward;
	t_vector	cam_dir;
	t_vector	final_dir;

	//camera direction
	forward = vector_normalize(camera->orientation);
	setup_camera_basis(forward, &right, &up);

	//convert pixel coordinates to fit in the plane
	cam_dir.x = (2.0 * (x + 0.5) / (double)WIDTH - 1.0) * tan(camera->fov * 0.5 * (M_PI / 180.0));
	cam_dir.y = (1.0 - 2.0 * (y + 0.5) / (double)HEIGHT) * tan(camera->fov * 0.5 * (M_PI / 180.0) / ((double)WIDTH / (double)HEIGHT));
	
	//final ray direction
	final_dir = add_vectors(add_vectors(multiply_scalar(right, cam_dir.x), \
		multiply_scalar(up, cam_dir.y)), forward);
	return (vector_normalize(final_dir));
}
