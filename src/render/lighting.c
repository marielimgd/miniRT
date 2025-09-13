/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:35:55 by marieli           #+#    #+#             */
/*   Updated: 2025/09/13 20:15:55 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color	compute_specular(t_material m, t_light *light, t_comps *comps, t_vector lightv)
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

t_color	lighting(t_material m, t_light *light, t_comps *comps)
{
	t_color		ambient, diffuse, specular;
	t_color		effective_color;
	t_vector	lightv;
	double		light_dot_normal;

	effective_color = multiply_color(m.color, light->color);
	subtract_tuples(&lightv, &light->origin, &comps->point);
	normalization(&lightv, &lightv);
	
	ambient = scale_color(effective_color, m.ambient);

	light_dot_normal = dot_product(&lightv, &comps->normalv);
	if (light_dot_normal < 0)
	{
		diffuse = (t_color){0, 0, 0};
		specular = (t_color){0, 0, 0};
	}
	else
	{
		diffuse = scale_color(effective_color, m.diffuse * light_dot_normal);
		specular = compute_specular(m, light, comps, lightv);
	}
	return (add_color(add_color(ambient, diffuse), specular));
}
