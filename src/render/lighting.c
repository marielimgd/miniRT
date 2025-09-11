/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:35:55 by marieli           #+#    #+#             */
/*   Updated: 2025/09/11 19:45:39 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color	compute_diffuse_component(t_material m, t_light *light, t_lighting_data d, t_color effective_color)
{
	t_vector	lightv;
	t_vector	*temp_v;
	double		light_dot_normal;
	t_color		result;

	temp_v = subtract_tuples(&light->origin, &d.point);
	lightv = *normalization(temp_v);
	free(temp_v);
	light_dot_normal = dot_product(&lightv, &d.normalv);
	if (light_dot_normal < 0)
	{
		return ((t_color){0, 0, 0});
	}
	result = scale_color(effective_color, m.diffuse * light_dot_normal);
	return (result);
}

t_color	lighting(t_material m, t_light *light, t_lighting_data d)
{
	t_color	effective_color;
	t_color	ambient;
	t_color	diffuse;
	t_color	result;

	effective_color = scale_color(m.color, light->brightness);
	ambient = scale_color(effective_color, m.ambient);
	diffuse = compute_diffuse_component(m, light, d, effective_color);
	result = add_color(ambient, diffuse);
	return (result);
}
