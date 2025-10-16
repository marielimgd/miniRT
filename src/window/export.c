/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:05:48 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/16 14:06:51 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	validate_scene(t_scene *scene)
{
	if (!scene->has_camera)
		parse_error(0, "Scene must have a camera 'C'");
	if (!scene->has_ambient)
		parse_error(0, "Scene must have ambient light 'A'");
	if (!scene->lights)
		parse_error(0, "Scene must have at least one light 'L'");
}

void	validate_filename(char *filename)
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

void	export_bmp(t_scene *world)
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