/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:46:11 by jhualves          #+#    #+#             */
/*   Updated: 2025/09/03 22:23:28 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_color	scale_color(t_color c, float ratio)
{
	t_color	color;

	color.red = (int)(c.red * ratio);
	color.green = (int)(c.green * ratio);
	color.blue = (int)(c.blue * ratio);
	return (color);
}
/*
	Calibrar para deixar menor que 255 a maior que 0;
*/
t_color	max_color(t_color c)
{
	t_color	final;

	final.red = fmin(255, fmax(0, c.red));
	final.green = fmin(255, fmax(0, c.green));
	final.blue = fmin(255, fmax(0, c.blue));
	return (final);
}

t_color	add_color(t_color a; t_color b)
{
	t_color	color;

	color.red = a.red + b.red;
	color.green = a.green + b.green;
	color.blue = a.blue + b.blue;
	color = max_color(color);
	return (color);
}
