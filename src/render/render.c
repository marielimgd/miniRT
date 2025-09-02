/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:17:26 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/02 19:34:04 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color	get_ray_color(t_vector ray_direction)
{
	t_color	color;

	color.r = (int)((ray_direction.x + 1.0) * 0.5 * 255);
	color.g = (int)((ray_direction.y + 1.0) * 0.5 * 255);
	color.b = (int)((ray_direction.z + 1.0) * 0.5 * 255);
	return (color);
}

void	render_scene(t_scene *scene)
{
	int			x;
	int			y;
	t_ray		ray;
	t_color		pixel_color;
	
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray.origin = scene->camera.origin;
			ray.direction = calculate_ray_direction(&scene->camera, x, y);
			pixel_color = get_ray_color(ray.direction);
			my_mlx_pixel_put(&scene->mlx, x, y, pixel_color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr,
		scene->mlx.img_ptr, 0, 0);
}
