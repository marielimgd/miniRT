/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:35:55 by marieli           #+#    #+#             */
/*   Updated: 2025/09/12 17:13:08 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color	compute_specular(t_material m, t_light *light, t_lighting_data d, t_vector lightv)
{
    t_vector	neg_lightv;
    t_vector	reflectv;
    double		reflect_dot_eye;
    double		factor;

    negative_vector(&neg_lightv, &lightv);
    reflect(&reflectv, &neg_lightv, &d.normalv);
    reflect_dot_eye = dot_product(&reflectv, &d.eyev);
	if (reflect_dot_eye <= 0)
		return ((t_color){0, 0, 0});
	factor = pow(reflect_dot_eye, m.shininess);
	return (scale_color(light->color, m.specular * factor));
}

t_color	lighting(t_material m, t_light *light, t_lighting_data d)
{
    t_color		final_color;
    t_color		effective_color;
    t_vector	lightv;
    t_vector	temp_v;
    double		light_dot_normal;

effective_color = scale_color(m.color, light->brightness);
	final_color = scale_color(effective_color, m.ambient);
	subtract_tuples(&temp_v, &light->origin, &d.point);
	normalization(&lightv, &temp_v);
	light_dot_normal = dot_product(&lightv, &d.normalv);
	if (light_dot_normal >= 0)
	{
		final_color = add_color(final_color,
				scale_color(effective_color, m.diffuse * light_dot_normal));
		final_color = add_color(final_color,
				compute_specular(m, light, d, lightv));
	}
	return (final_color);
}

