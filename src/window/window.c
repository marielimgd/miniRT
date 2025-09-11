/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:17:32 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/11 20:48:22 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	close_window(t_scene *scene)
{
	mlx_destroy_image(scene->mlx.mlx_ptr, scene->mlx.img_ptr);
	mlx_destroy_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	mlx_destroy_display(scene->mlx.mlx_ptr);
	free(scene->mlx.mlx_ptr);
	free_all();
	exit(0);
	return (0);
}

int	handle_keypress(int keycode, t_scene *scene)
{
	bool	needs_rerender;

	needs_rerender = false;
	if (keycode == ESC_KEY)
		close_window(scene);
	else if (keycode == SPACE_KEY)
	{
		randomize_object_colors(scene);
		needs_rerender = true;
	}
	else if (keycode == PLUS_KEY)
	{
		scene->camera.fov -= 5;
		if (scene->camera.fov < 1)
			scene->camera.fov = 1;
		needs_rerender = true;
	}
	else if (keycode == MINUS_KEY)
	{
		scene->camera.fov += 5;
		if (scene->camera.fov > 179)
			scene->camera.fov = 179;
		needs_rerender = true;
	}
	if (needs_rerender)
		render_scene(scene);
	return (0);
}

int	handle_mouse_scroll(int button, int x, int y, t_scene *scene)
{
	(void)x;
	(void)y;
	if (button == MOUSE_SCROLL_UP)
	{
		scene->camera.fov -= 5;
		if (scene->camera.fov < 1)
			scene->camera.fov = 1;
		render_scene(scene);
	}
	else if (button == MOUSE_SCROLL_DOWN)
	{
		scene->camera.fov += 5;
		if (scene->camera.fov > 179)
			scene->camera.fov = 179;
		render_scene(scene);
	}
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
	mlx_mouse_hook(scene->mlx.win_ptr, handle_mouse_scroll, scene);
	mlx_hook(scene->mlx.win_ptr, 17, 0, close_window, scene);
}
