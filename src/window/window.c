/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:34:37 by jhualves          #+#    #+#             */
/*   Updated: 2025/10/23 15:34:37 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	close_window(t_scene *scene)
{
	(void)scene;
	free_all();
	exit(0);
	return (0);
}

static void	init_mlx_connection(t_mlx_data *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		parse_error(0, "Failed to initialize MLX");
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "miniRT");
	if (!mlx->win_ptr)
		parse_error(0, "Failed to create window");
}

static void	init_mlx_image(t_mlx_data *mlx)
{
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	if (!mlx->img_ptr)
		parse_error(0, "Failed to create image");
	mlx->addr = mlx_get_data_addr(mlx->img_ptr, &mlx->bpp,
			&mlx->line_len, &mlx->endian);
}

static void	setup_hooks(t_scene *scene)
{
	mlx_hook(scene->mlx.win_ptr, 2, (1L << 0), handle_keypress, scene);
	mlx_mouse_hook(scene->mlx.win_ptr, handle_mouse_scroll, scene);
	mlx_hook(scene->mlx.win_ptr, 17, 0, close_window, scene);
}

void	init_window(t_scene *scene)
{
	init_mlx_connection(&scene->mlx);
	init_mlx_image(&scene->mlx);
	setup_hooks(scene);
}
