/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:05:44 by jhualves          #+#    #+#             */
/*   Updated: 2025/10/23 16:05:44 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * create_cylinder
 * Allocates and initializes a cylinder object with default diameter=2 height=2
 */
t_object	*create_cylinder(void)
{
	t_object	*cylinder;

	cylinder = malloc(sizeof(t_object));
	if (!cylinder)
		print_error("Failed to allocate cylinder");
	cylinder->type = CYLINDER;
	cylinder->transform = identity_matrix();
	cylinder->inverse_transform = inverse_matrix(cylinder->transform);
	cylinder->transpose_inverse_transform = \
	transpose_matrix(cylinder->inverse_transform);
	cylinder->origin = (t_vector){0, 0, 0, 1};
	cylinder->prop.cylinder.diameter = 2.0;
	cylinder->prop.cylinder.height = 2.0;
	return (cylinder);
}

static int	check_cylinder_height(t_ray *ray, double t, double height)
{
	double	y;

	y = ray->origin.y + t * ray->direction.y;
	if (y < -height / 2.0 || y > height / 2.0)
		return (0);
	return (1);
}

static void	calc_cylinder_coeffs(t_ray *ray, double radius, double *coeffs)
{
	coeffs[0] = ray->direction.x * ray->direction.x
		+ ray->direction.z * ray->direction.z;
	coeffs[1] = 2.0 * (ray->origin.x * ray->direction.x
			+ ray->origin.z * ray->direction.z);
	coeffs[2] = ray->origin.x * ray->origin.x
		+ ray->origin.z * ray->origin.z - radius * radius;
}

static t_intersection_list	make_cyl_intersections(t_ray *ray,
	double *coeffs, double disc, t_object *cyl)
{
	double	t[2];
	int		valid[2];

	t[0] = (-coeffs[1] - sqrt(disc)) / (2.0 * coeffs[0]);
	t[1] = (-coeffs[1] + sqrt(disc)) / (2.0 * coeffs[0]);
	valid[0] = check_cylinder_height(ray, t[0], cyl->prop.cylinder.height);
	valid[1] = check_cylinder_height(ray, t[1], cyl->prop.cylinder.height);
	if (valid[0] && valid[1])
		return (create_intersections_list(2,
				create_intersection(t[0], cyl),
				create_intersection(t[1], cyl)));
	if (valid[0])
		return (create_intersections_list(1,
				create_intersection(t[0], cyl)));
	if (valid[1])
		return (create_intersections_list(1,
				create_intersection(t[1], cyl)));
	return ((t_intersection_list){0, 0, NULL});
}

/*
 * intersect_cylinder
 * Intersects a ray with a cylinder aligned with the y-axis. Cylinder in object
 * space has radius = diameter/2 and extends from -height/2 to +height/2 on y.
 */
t_intersection_list	intersect_cylinder(t_object *cylinder, t_ray ray)
{
	t_ray				transformed_ray;
	double				coeffs[3];
	double				discriminant;
	double				radius;

	transformed_ray = transform(ray, cylinder->inverse_transform);
	radius = cylinder->prop.cylinder.diameter / 2.0;
	calc_cylinder_coeffs(&transformed_ray, radius, coeffs);
	if (fabs(coeffs[0]) < EPSILON)
		return ((t_intersection_list){0, 0, NULL});
	discriminant = coeffs[1] * coeffs[1] - 4.0 * coeffs[0] * coeffs[2];
	if (discriminant < 0)
		return ((t_intersection_list){0, 0, NULL});
	return (make_cyl_intersections(&transformed_ray, coeffs, discriminant, \
		cylinder));
}
