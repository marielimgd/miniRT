/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:59:26 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/11 19:30:47 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*create_sphere(void)
{
	t_object *sphere;
	
	sphere = safe_malloc(sizeof(t_object), ALLOC_TYPE_GENERIC);
	sphere->type = SPHERE;
	sphere->transform = identity_matrix();
	sphere->origin = (t_vector){0, 0, 0, 1};
	sphere->prop.sphere.radius = 1.0;
	return(sphere);
}

static t_intersection_list	make_intersections(double t1, double t2, t_object *sphere)
{
	t_intersection	i1;
	t_intersection	i2;

	i1 = create_intersection(t1, sphere);
	i2 = create_intersection(t2, sphere);
	return (create_intersections_list(2, i1, i2));
}

static void	calculate_sphere_coeffs(t_ray *ray, t_object *sphere, double *coeffs)
{
	t_vector	*sphere_to_ray;
	t_vector	origin_point;

	origin_point = create_point(0, 0, 0);
	sphere_to_ray = subtract_tuples(&ray->origin, &origin_point);


	coeffs[0] = dot_product(&ray->direction, &ray->direction);
	coeffs[1] = 2 * dot_product(&ray->direction, sphere_to_ray);
	coeffs[2] = dot_product(sphere_to_ray, sphere_to_ray) - (sphere->prop.sphere.radius * sphere->prop.sphere.radius);
	free(sphere_to_ray);
}

t_intersection_list	intersect_sphere(t_object *sphere, t_ray ray)
{
	t_ray		transformed_ray;
	t_matrix	*inv_matrix;
	double		coeffs[3];
	double		discriminant;

	inv_matrix = inverse_matrix(sphere->transform);
	transformed_ray = transform(ray, inv_matrix);

	calculate_sphere_coeffs(&transformed_ray, sphere, coeffs);
	discriminant = (coeffs[1] * coeffs[1]) - 4 * coeffs[0] * coeffs[2];

	if (discriminant < 0)
		return ((t_intersection_list){.count = 0});

	return (make_intersections(
			(-coeffs[1] - sqrt(discriminant)) / (2 * coeffs[0]),
			(-coeffs[1] + sqrt(discriminant)) / (2 * coeffs[0]),
			sphere));
}


static t_vector	*get_object_space_normal(t_vector world_point, t_matrix *inv_transform)
{
	t_vector	object_point;
	t_vector	origin_point;
	t_vector	*object_normal;
	t_vector	*result;

	object_point = multiply_matrix_by_tuple(inv_transform, world_point);
	origin_point = create_point(0, 0, 0);
	object_normal = subtract_tuples(&object_point, &origin_point);
	result = safe_malloc(sizeof(t_vector), ALLOC_TYPE_GENERIC);
	*result = *object_normal;
	free(object_normal);
	return (result);
}


static t_vector	get_world_space_normal(t_vector *object_normal, t_matrix *inv_transform)
{
	t_matrix	*transposed_inv;
	t_vector	world_normal;

	transposed_inv = transpose_matrix(inv_transform);
	world_normal = multiply_matrix_by_tuple(transposed_inv, *object_normal);
	world_normal.w = 0;
	free_matrix(transposed_inv);
	return (world_normal);
}

t_vector	normal_at_sphere(t_object *sphere, t_vector world_point)
{
	t_matrix	*inv_transform;
	t_vector	object_normal;
	t_vector	world_normal;
	t_vector	*normalized_normal;
	t_vector	final_normal;

	inv_transform = inverse_matrix(sphere->transform);
	t_vector *object_normal_ptr;

	object_normal_ptr = get_object_space_normal(world_point, inv_transform);
	object_normal = *object_normal_ptr;
	world_normal = get_world_space_normal(&object_normal, inv_transform);
	normalized_normal = normalization(&world_normal);
	final_normal = *normalized_normal;

	free_matrix(inv_transform);
	free(object_normal_ptr);
	free(normalized_normal);
	return (final_normal);
}
