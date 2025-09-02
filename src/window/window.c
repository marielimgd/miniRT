/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:17:32 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/02 18:17:36 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	close_window(t_scene *scene)
{
	mlx_destroy_image(scene->mlx.mlx_ptr, scene->mlx.img_ptr);
	mlx_destroy_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	mlx_destroy_display(scene->mlx.mlx_ptr);
	free(scene->mlx.mlx_ptr);
	// TODO: Free all allocated scene data (lights, objects)
	exit(0);
	return (0);
}

int	handle_keypress(int keycode, t_scene *scene)
{
	if (keycode == ESC_KEY)
		close_window(scene);
	return (0);
}

void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, t_color color)
{
	char	*dst;
	int		rgb_int;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	rgb_int = (color.r << 16) | (color.g << 8) | color.b;
	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = rgb_int;
}

void	init_window(t_scene *scene)
{
	scene->mlx.mlx_ptr = mlx_init();
	if (!scene->mlx.mlx_ptr)
		parse_error("Failed to initialize MLX");
	scene->mlx.win_ptr = mlx_new_window(scene->mlx.mlx_ptr, WIDTH, HEIGHT, "miniRT");
	if (!scene->mlx.win_ptr)
		parse_error("Failed to create window");
	scene->mlx.img_ptr = mlx_new_image(scene->mlx.mlx_ptr, WIDTH, HEIGHT);
	if (!scene->mlx.img_ptr)
		parse_error("Failed to create image");
	scene->mlx.addr = mlx_get_data_addr(scene->mlx.img_ptr, &scene->mlx.bpp,
			&scene->mlx.line_len, &scene->mlx.endian);
	mlx_key_hook(scene->mlx.win_ptr, handle_keypress, scene);
	mlx_hook(scene->mlx.win_ptr, 17, 0, close_window, scene);
}
