/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:59:26 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/04 19:27:35 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*create_sphere(void)
{
	t_object *sphere;
	
	sphere = safe_malloc(sizeof(t_object), ALLOC_TYPE_GENERIC);
	sphere->type = SPHERE;
	//add sphere properties later
	return(sphere);
}

static t_intersect_list make_intersections(double t1, double t2, t_object *sphere)
{
	t_intersection	i1;
	t_intersection 	i2;

	i1 = create_intersection(t1, sphere);
	i2 = create_intersection(t2, sphere);

	return(create_intersections_list(2, i1, i2));
}


t_intersect_list		intersect_sphere(t_object *sphere, t_ray ray)
{
	t_vector			*sphere_to_ray;
	double				a;
	double				b;
	double				c;
	double				discriminant;
	t_intersect_list	x;

	(void)sphere;
	sphere_to_ray = subtract_tuples(&ray.origin, &(t_vector){0, 0, 0, 1});
	a = dot_product(&ray.direction, &ray.direction);
	b = 2 * dot_product(&ray.direction, sphere_to_ray);
	c = dot_product(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = (b * b) - 4 * a * c;

	if (discriminant < 0) // if ray misses the sphere
		return ((t_intersect_list){.count = 0});
	
	x = make_intersections((-b - sqrt(discriminant)) / (2 * a), (-b + sqrt(discriminant)) / (2 * a), sphere);
	
	return(x);	
}
