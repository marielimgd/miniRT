/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:46:11 by jhualves          #+#    #+#             */
/*   Updated: 2025/09/04 15:31:28 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/*
	Calibrar para deixar menor que 255 a maior que 0;
*/
t_color	max_color(t_color c)
{
	t_color	final;

	final.r = fmin(255, fmax(0, c.r));
	final.g = fmin(255, fmax(0, c.g));
	final.b = fmin(255, fmax(0, c.b));
	return (final);
}

t_color	scale_color(t_color c, float ratio)
{
	t_color	color;

	color.r = (int)(c.r * ratio);
	color.g = (int)(c.g * ratio);
	color.b = (int)(c.b * ratio);
	color = max_color(color);
	return (color);
}

t_color	add_color(t_color a, t_color b)
{
	t_color	color;

	color.r = a.r + b.r;
	color.g = a.g + b.g;
	color.b = a.b + b.b;
	color = max_color(color);
	return (color);
}

t_color	subtract_color(t_color a, t_color b)
{
	t_color	color;

	color.r = a.r - b.r;
	color.g = a.g - b.g;
	color.b = a.b - b.b;
	color = max_color(color);
	return (color);
}

t_color	multiply_color(t_color a, t_color b)
{
	t_color	color;

	color.r = a.r * b.r;
	color.g = a.g * b.g;
	color.b = a.b * b.b;
	color = max_color(color);
	return (color);
}
