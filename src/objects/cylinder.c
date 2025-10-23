/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:38:03 by jhualves          #+#    #+#             */
/*   Updated: 2025/10/23 15:38:03 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*create_cylinder(void)
{
	t_object	*cylinder;

	cylinder = malloc(sizeof(t_object));
	cylinder->type = CYLINDER;
	cylinder->transform = identity_matrix();
	cylinder->inverse_transform = inverse_matrix(cylinder->transform);
	cylinder->transpose_inverse_transform = transpose_matrix(
			cylinder->inverse_transform);
	cylinder->origin = (t_vector){0, 0, 0, 1};
	cylinder->prop.cylinder.radius = 1.0;
	return (cylinder);
}

static t_intersection_list	make_intersections(double t1, double t2,
		t_object *sphere)
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
	t_ray				transformed_ray;
	double				coeffs[3];
	double				discriminant;
	t_intersection_list	empty_list;

	transformed_ray = transform(ray, sphere->inverse_transform);
	calculate_sphere_coeffs(&transformed_ray, coeffs);
	discriminant = (coeffs[1] * coeffs[1]) - 4 * coeffs[0] * coeffs[2];
	if (discriminant < 0)
	{
		empty_list.count = 0;
		empty_list.intersections = NULL;
		return (empty_list);
	}
	return (make_intersections(
			(-coeffs[1] - sqrt(discriminant)) / (2 * coeffs[0]),
			(-coeffs[1] + sqrt(discriminant)) / (2 * coeffs[0]),
			sphere));
}
