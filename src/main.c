/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:17:41 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/22 20:13:53 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_scene	*world;
	bool	save_to_bmp;

	if (argc < 2 || argc > 3)
		parse_error(0, "Usage: ./minirt <scene.rt> [--save]");
	if (argc == 3 && ft_strcmp(argv[2], "--save") != 0)
		parse_error(0,
			"Invalid argument. Use '--save' to create a BMP file.");
	save_to_bmp = (argc == 3);
	validate_filename(argv[1]);
	world = create_world();
	parse_scene(argv[1], world);
	validate_scene(world);
	world->selected_light = world->lights;
	print_initial_object_selection(world);
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
