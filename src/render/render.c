/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:17:26 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/11 20:14:18 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* static t_color	get_ray_color(t_vector ray_direction)
{
	t_color	color;

	color.r = (int)((ray_direction.x + 1.0) * 0.5 * 255);
	color.g = (int)((ray_direction.y + 1.0) * 0.5 * 255);
	color.b = (int)((ray_direction.z + 1.0) * 0.5 * 255);
	return (color);
} */

void	render_scene(t_scene *scene)
{
	int				x;
	int				y;
	t_ray			ray;
	t_color			pixel_color;
	t_intersection	hit;
	
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray.origin = scene->camera.origin;
			ray.direction = calculate_ray_direction(&scene->camera, x, y);
			hit = intersect_world(scene, ray);
			if (hit.object != NULL)
				pixel_color = shade_hit(scene, hit, ray);
			else
				pixel_color = (t_color){0, 0, 0};
			my_mlx_pixel_put(&scene->mlx, x, y, pixel_color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr, scene->mlx.img_ptr, 0, 0);
}
