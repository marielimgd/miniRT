/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 19:00:00 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/16 19:05:41 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_object_info(t_object *obj)
{
	double	pos_x;
	double	pos_y;
	double	pos_z;

	pos_x = obj->transform->matrix[0][3];
	pos_y = obj->transform->matrix[1][3];
	pos_z = obj->transform->matrix[2][3];
	if (obj->type == SPHERE)
		printf("Selected: SPHERE | Diameter: %.2f | "
			"Position: (%.1f, %.1f, %.1f)\n",
			obj->prop.sphere.radius * 2.0, pos_x, pos_y, pos_z);
	else if (obj->type == PLANE)
		printf("Selected: PLANE | Position: (%.1f, %.1f, %.1f)\n",
			pos_x, pos_y, pos_z);
	else if (obj->type == CYLINDER)
		printf("Selected: CYLINDER | Diameter: %.2f | Height: %.2f"
			" | Position: (%.1f, %.1f, %.1f)\n",
			obj->prop.cylinder.diameter, obj->prop.cylinder.height,
			pos_x, pos_y, pos_z);
}

void	resize_sphere(t_object *obj, int keycode, bool *needs_rerender)
{
	t_matrix	*translation_m;
	t_matrix	*scaling_m;
	double		pos[3];

	pos[0] = obj->transform->matrix[0][3];
	pos[1] = obj->transform->matrix[1][3];
	pos[2] = obj->transform->matrix[2][3];
	if (keycode == KEY_COMMA)
		obj->prop.sphere.radius -= 0.1;
	else if (keycode == KEY_DOT)
		obj->prop.sphere.radius += 0.1;
	else
		return ;
	if (obj->prop.sphere.radius < 0.01)
		obj->prop.sphere.radius = 0.01;
	translation_m = translation(pos[0], pos[1], pos[2]);
	scaling_m = scaling(obj->prop.sphere.radius,
			obj->prop.sphere.radius, obj->prop.sphere.radius);
	set_transform(obj, matrix_product(translation_m, scaling_m));
	free_matrix(translation_m);
	free_matrix(scaling_m);
	printf("\n=== Sphere Resized ===\n");
	print_object_info(obj);
	*needs_rerender = true;
}

void	resize_cylinder_diameter(t_object *obj, int keycode,
		bool *needs_rerender)
{
	t_matrix	*translation_m;
	t_matrix	*scaling_m;
	double		pos[3];

	pos[0] = obj->transform->matrix[0][3];
	pos[1] = obj->transform->matrix[1][3];
	pos[2] = obj->transform->matrix[2][3];
	if (keycode == KEY_COMMA)
		obj->prop.cylinder.diameter -= 0.1;
	else if (keycode == KEY_DOT)
		obj->prop.cylinder.diameter += 0.1;
	else
		return ;
	if (obj->prop.cylinder.diameter < 0.01)
		obj->prop.cylinder.diameter = 0.01;
	translation_m = translation(pos[0], pos[1], pos[2]);
	scaling_m = scaling(obj->prop.cylinder.diameter / 2.0,
			1.0, obj->prop.cylinder.diameter / 2.0);
	set_transform(obj, matrix_product(translation_m, scaling_m));
	free_matrix(translation_m);
	free_matrix(scaling_m);
	printf("\n=== Cylinder Diameter Changed ===\n");
	print_object_info(obj);
	*needs_rerender = true;
}

void	resize_cylinder_height(t_object *obj, int keycode,
		bool *needs_rerender)
{
	if (keycode == KEY_H)
		obj->prop.cylinder.height += 0.1;
	else if (keycode == KEY_G)
	{
		obj->prop.cylinder.height -= 0.1;
		if (obj->prop.cylinder.height < 0.01)
			obj->prop.cylinder.height = 0.01;
	}
	else
		return ;
	printf("\n=== Cylinder Height Changed ===\n");
	print_object_info(obj);
	*needs_rerender = true;
}

void	cycle_object_selection(t_scene *scene, bool *needs_rerender)
{
	t_object	*obj;

	scene->selected_object = scene->selected_object->next;
	if (scene->selected_object == NULL)
		scene->selected_object = scene->objects;
	obj = (t_object *)scene->selected_object->data;
	printf("\n=== Object Selection Changed ===\n");
	print_object_info(obj);
	*needs_rerender = true;
}
