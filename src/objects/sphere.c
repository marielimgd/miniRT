/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:59:26 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/12 17:26:17 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*create_sphere(void)
{
	t_object *sphere;
	
	sphere = malloc(sizeof(t_object));
	sphere->type = SPHERE;
	sphere->transform = identity_matrix();
	sphere->inverse_transform = inverse_matrix(sphere->transform);
	sphere->transpose_inverse_transform = transpose_matrix(sphere->inverse_transform);
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

static void	calculate_sphere_coeffs(t_ray *ray, double *coeffs)
{
	t_vector	sphere_to_ray;
	t_vector	origin_point;

	origin_point = create_point(0, 0, 0);
	subtract_tuples(&sphere_to_ray, &ray->origin, &origin_point);
	coeffs[0] = dot_product(&ray->direction, &ray->direction);
	coeffs[1] = 2 * dot_product(&ray->direction, &sphere_to_ray);
	coeffs[2] = dot_product(&sphere_to_ray, &sphere_to_ray) - 1;
}

t_intersection_list	intersect_sphere(t_object *sphere, t_ray ray)
{
	t_ray		transformed_ray;
	double		coeffs[3];
	double		discriminant;

	transformed_ray = transform(ray, sphere->inverse_transform);
	calculate_sphere_coeffs(&transformed_ray, coeffs);
	discriminant = (coeffs[1] * coeffs[1]) - 4 * coeffs[0] * coeffs[2];
	if (discriminant < 0)
		return ((t_intersection_list){.count = 0});
	return (make_intersections(
			(-coeffs[1] - sqrt(discriminant)) / (2 * coeffs[0]),
			(-coeffs[1] + sqrt(discriminant)) / (2 * coeffs[0]),
			sphere));
}

static void	get_object_space_normal(t_vector *result, t_vector *world_point,
		t_matrix *inv_transform)
{
	t_vector	object_point;
	t_vector	origin_point;

	object_point = multiply_matrix_by_tuple(inv_transform, *world_point);
	origin_point = create_point(0, 0, 0);
	subtract_tuples(result, &object_point, &origin_point);
}

static void	get_world_space_normal(t_vector *result, t_vector *object_normal,
		t_matrix *transpose_inv_transform)
{
	*result = multiply_matrix_by_tuple(transpose_inv_transform, *object_normal);
	result->w = 0;
}

t_vector	normal_at_sphere(t_object *sphere, t_vector world_point)
{
	t_vector	object_normal;
	t_vector	world_normal;
	t_vector	final_normal;

	get_object_space_normal(&object_normal, &world_point, sphere->inverse_transform);
	get_world_space_normal(&world_normal, &object_normal, sphere->transpose_inverse_transform);
	normalization(&final_normal, &world_normal);
	return (final_normal);
}
