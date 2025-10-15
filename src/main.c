/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:17:41 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/15 19:28:33 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* int	main(int argc, char **argv)
{
	t_scene	*world;

	if (argc != 2)
		parse_error(0, "Usage: ./minirt <scene.rt>");
	world = create_world();
	parse_scene(argv[1], world);
	world->selected_light = world->lights;
	init_window(world);
	render_scene(world);
	mlx_loop(world->mlx.mlx_ptr);
	free_all();
	return (0);
} */

/* ---mouse control---
W, A, S, D: Move the camera forward, left, backward, and right.

Arrow Keys: Rotate the camera's view.

L: Cycle through the light sources in your scene.

+/-: Increase or decrease the brightness of the currently selected light 
*/

//----------------------------------------------TEST AREA----------------------------------------


static void	validate_scene(t_scene *scene)
{
	if (!scene->has_camera)
		parse_error(0, "Scene must have a camera 'C'");
	if (!scene->has_ambient)
		parse_error(0, "Scene must have ambient light 'A'");
	if (!scene->lights)
		parse_error(0, "Scene must have at least one light 'L'");
}

static void	validate_filename(char *filename)
{
	const char	*extension = ".rt";
	int			file_len;
	int			ext_len;

	file_len = ft_strlen(filename);
	ext_len = ft_strlen(extension);
	if (file_len <= ext_len
		|| ft_strcmp(filename + file_len - ext_len, extension) != 0)
		parse_error(0, "Scene file must have a .rt extension");
}

static void	export_bmp(t_scene *world)
{
	t_vector	to;

	world->mlx.mlx_ptr = mlx_init();
	world->mlx.img_ptr = mlx_new_image(world->mlx.mlx_ptr, WIDTH, HEIGHT);
	world->mlx.addr = mlx_get_data_addr(world->mlx.img_ptr, &world->mlx.bpp,
			&world->mlx.line_len, &world->mlx.endian);
	normalization(&world->camera.orientation, &world->camera.orientation);
	add_tuples(&to, &world->camera.from, &world->camera.orientation);
	world->camera.transform = view_transform(world->camera.from, to,
			world->camera.up);
	render_scene(world);
	export_to_bitmap("render.bmp", world);
}

int	main(int argc, char **argv)
{
	t_scene	*world;
	bool	save_to_bmp;

	if (argc < 2 || argc > 3)
		parse_error(0, "Usage: ./minirt <scene.rt> [--save]");
	if (argc == 3 && ft_strcmp(argv[2], "--save") != 0)
		parse_error(0, "Invalid argument. Use '--save' to create a BMP file.");
	save_to_bmp = (argc == 3);
	validate_filename(argv[1]);
	world = create_world();
	parse_scene(argv[1], world);
	validate_scene(world);
	world->selected_light = world->lights;
	if (save_to_bmp)
		export_bmp(world);
	else
	{
		init_window(world);
		render_scene(world);
		mlx_loop(world->mlx.mlx_ptr);
	}
	free_all();
	return (0);
}

