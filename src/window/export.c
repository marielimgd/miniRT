/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:05:48 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/16 16:17:43 by mmariano         ###   ########.fr       */
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

void	print_initial_object_selection(t_scene *scene)
{
	t_object	*obj;
	double		pos_x;
	double		pos_y;
	double		pos_z;

	if (!scene->selected_object || !scene->selected_object->data)
	{
		printf("\nNo objects in scene to select.\n");
		return ;
	}
	obj = (t_object *)scene->selected_object->data;
	/* Extract position from transform matrix */
	pos_x = obj->transform->matrix[0][3];
	pos_y = obj->transform->matrix[1][3];
	pos_z = obj->transform->matrix[2][3];
	
	printf("\n=== Initial Object Selection ===\n");
	if (obj->type == SPHERE)
		printf("Selected: SPHERE | Diameter: %.2f | Position: (%.1f, %.1f, %.1f)\n",
			obj->prop.sphere.radius * 2.0, pos_x, pos_y, pos_z);
	else if (obj->type == PLANE)
		printf("Selected: PLANE | Position: (%.1f, %.1f, %.1f)\n",
			pos_x, pos_y, pos_z);
	else if (obj->type == CYLINDER)
		printf("Selected: CYLINDER | Diameter: %.2f | Height: %.2f | Position: (%.1f, %.1f, %.1f)\n",
			obj->prop.cylinder.diameter, obj->prop.cylinder.height,
			pos_x, pos_y, pos_z);
	printf("\nControls:\n");
	printf("  O: Cycle selected object\n");
	printf("  , (comma): Decrease diameter\n");
	printf("  . (dot): Increase diameter\n");
	printf("  H: Increase cylinder height\n");
	printf("  G: Decrease cylinder height\n\n");
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
	if (fabs(world->camera.orientation.y) > 0.999)
		world->camera.up = create_vector(0, 0, 1);
	else
		world->camera.up = create_vector(0, 1, 0);
	add_tuples(&to, &world->camera.from, &world->camera.orientation);
	world->camera.transform = view_transform(world->camera.from, to,
			world->camera.up);
	render_scene(world);
	export_to_bitmap("render.bmp", world);
}