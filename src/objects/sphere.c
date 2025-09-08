/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:59:26 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/08 16:18:29 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*create_sphere(void)
{
	t_object *sphere;
	
	sphere = safe_malloc(sizeof(t_object), ALLOC_TYPE_GENERIC);
	sphere->type = SPHERE;
	//add other sphere properties later
	return(sphere);
}

static t_intersection_list make_intersections(double t1, double t2, t_object *sphere)
{
	t_intersection	i1;
	t_intersection 	i2;

	i1 = create_intersection(t1, sphere);
	i2 = create_intersection(t2, sphere);

	return(create_intersections_list(2, i1, i2));
}
static double coeficient_calculation(t_object *sphere, t_ray ray, double *a, double *b, double *c)
{
	t_vector	*sphere_to_ray;

	sphere_to_ray = subtract_tuples(&ray.origin, &sphere->origin);
	*a = dot_product(&ray.direction, &ray.direction);
	*b = 2 * dot_product(&ray.direction, sphere_to_ray);
	*c = dot_product(sphere_to_ray, sphere_to_ray) - (sphere->prop.sphere.radius * sphere->prop.sphere.radius);
	free(sphere_to_ray);
}

t_intersection_list	intersect_sphere(t_object *sphere, t_ray ray)
{
	t_ray				transformed_ray;
	t_matrix			*inv_matrix;
	double				coeff[3];
	double				discriminant;
	t_intersection_list		x;

	inv_matrix = inverse_matrix(sphere->transform);
	transformed_ray = transform(ray, inv_matrix);
	free_matrix(inv_matrix);
	discriminant = (sphere, transformed_ray, &coeff[0], &coeff[1], &coeff[2]);
	if (discriminant < 0)
		return ((t_intersection_list){.count = 0});

	x = make_intersections(
			(-coeff[1] - sqrt(discriminant)) / (2 * coeff[0]),
			(-coeff[1] + sqrt(discriminant)) / (2 * coeff[0]),
			sphere);

	return(x);
}

