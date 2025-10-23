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

/*
 * intersect_cylinder
 * Intersects a ray with a cylinder aligned with the y-axis. Cylinder in object
 * space has radius = diameter/2 and extends from -height/2 to +height/2 on y.
 */
// t_intersection_list intersect_cylinder(t_object *cylinder, t_ray ray)
// {
// 	/*
// 	 * Skeleton for intersect_cylinder
// 	 * TODOs below show the minimal steps to implement. Fill each section
// 	 * and remove temporary returns as you complete the implementation.
// 	 */

// 	t_ray                   tr;
// 	double                  ox;
// 	double                  oy;
// 	double                  oz;
// 	double                  dx;
// 	double                  dy;
// 	double                  dz;
// 	double                  radius;
// 	double                  half_height;
// 	double                  a;
// 	double                  b;
// 	double                  c;
// 	double                  disc;
// 	double                  t0;
// 	double                  t1;
// 	double                  cap_t;
// 	double                  candidates[4]; /* up to 4 candidate t values */
// 	int                     cand_count;
// 	t_intersection_list     list;
// 	t_intersection         *arr;
// 	int                     i;

// 	/* --- TODO 1: transform the ray to object space ---
// 	 * tr = transform(ray, cylinder->inverse_transform);
// 	 */

// 	/* --- TODO 2: extract components from tr ---
// 	 * ox = tr.origin.x; oy = tr.origin.y; oz = tr.origin.z;
// 	 * dx = tr.direction.x; dy = tr.direction.y; dz = tr.direction.z;
// 	 */

// 	/* --- TODO 3: compute radius/half_height from object properties ---
// 	 * radius = cylinder->prop.cylinder.diameter / 2.0;
// 	 * half_height = cylinder->prop.cylinder.height / 2.0;
// 	 */

// 	/* --- TODO 4: lateral surface intersection (quadratic in x,z) ---
// 	 * a = dx*dx + dz*dz;
// 	 * b = 2*(ox*dx + oz*dz);
// 	 * c = ox*ox + oz*oz - radius*radius;
// 	 * if (fabs(a) > EPSILON) compute disc = b*b - 4*a*c;
// 	 * if (disc >= 0) compute t0,t1 and for each verify
// 	 *    y = oy + t*dy is in [-half_height, half_height]
// 	 * if valid, push into candidates[cand_count++]
// 	 */

// 	/* --- TODO 5: caps intersections (top and bottom) ---
// 	 * if (fabs(dy) > EPSILON) {
// 	 *   top_t = (half_height - oy) / dy; check (ox + top_t*dx, oz + top_t*dz)
// 	 *   bottom_t = (-half_height - oy) / dy; check similarly
// 	 * }
// 	 */

// 	/* --- TODO 6: if no candidates, return empty list --- */

// 	/* --- TODO 7: sort candidates ascending (simple insertion/bubble sort) --- */

// 	/* --- TODO 8: allocate array of intersections and fill it ---
// 	 * arr = malloc(sizeof(t_intersection) * cand_count);
// 	 * for i in 0..cand_count-1: arr[i] = create_intersection(candidates[i], cylinder);
// 	 * list.count = cand_count; list.capacity = cand_count; list.intersections = arr;
// 	 * return list;
// 	 */

// 	/* temporary default: return empty list until implemented */
// 	list.count = 0;
// 	list.intersections = NULL;
// 	return (list);
// }

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
	return (make_cyl_intersections(&transformed_ray, coeffs, discriminant, cylinder));
}
