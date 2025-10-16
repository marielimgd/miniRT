/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:35:55 by marieli           #+#    #+#             */
/*   Updated: 2025/10/15 18:56:42 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color	compute_specular(t_material m, t_light *light,
	 t_comps *comps, t_vector lightv)
{
	t_vector	reflectv;
	t_vector	neg_lightv;
	double		reflect_dot_eye;
	double		factor;

	negative_vector(&neg_lightv, &lightv);
	reflect(&reflectv, &neg_lightv, &comps->normalv);
	reflect_dot_eye = dot_product(&reflectv, &comps->eyev);

	if (reflect_dot_eye <= 0)
		return ((t_color){0, 0, 0});

	factor = pow(reflect_dot_eye, m.shininess);
	return (scale_color(light->color, m.specular * factor));
}

static t_color	compute_lighting_effects(t_material m, t_light *light,
	 t_comps *comps)
{
	t_color		color;
	t_vector	lightv;
	double		light_dot_normal;
	double		distance;
	double		attenuation;

	subtract_tuples(&lightv, &light->origin, &comps->over_point);
	distance = get_magnitude(&lightv);
	normalization(&lightv, &lightv);
	light_dot_normal = dot_product(&lightv, &comps->normalv);
	if (light_dot_normal < 0)
		return ((t_color){0, 0, 0});
	attenuation = light->brightness;
	color = scale_color(multiply_color(m.color, light->color),
			m.diffuse * light_dot_normal * attenuation);
	color = add_color(color, compute_specular(m, light, comps, lightv));
	return (color);
}

t_color	lighting(t_material m, t_light *light, t_comps *comps,
	 bool in_shadow)
{
	t_color		final_color;

	final_color = (t_color){0, 0, 0};
	if (in_shadow)
		return (final_color);
	final_color = compute_lighting_effects(m, light, comps);
	return (final_color);
}
