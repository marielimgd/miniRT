/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:18:41 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/12 22:38:29 by mmariano         ###   ########.fr       */
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
