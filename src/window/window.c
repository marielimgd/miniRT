/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:17:32 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/16 14:00:56 by mmariano         ###   ########.fr       */
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
	/* Use mlx_hook for KeyPress (event 2) with mask (1L<<0) to ensure
	   non-printable keys like arrow keys are delivered correctly. */
	mlx_hook(scene->mlx.win_ptr, 2, (1L<<0), handle_keypress, scene);
	mlx_mouse_hook(scene->mlx.win_ptr, handle_mouse_scroll, scene);
	mlx_hook(scene->mlx.win_ptr, 17, 0, close_window, scene);
}

void	init_window(t_scene *scene)
{
	init_mlx_connection(&scene->mlx);
	init_mlx_image(&scene->mlx);
	setup_hooks(scene);
}
