/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 19:00:00 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/16 19:05:41 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	apply_translation(t_object *obj, int keycode, double step,
		bool *needs_rerender)
{
	t_matrix	*transform_update;
	t_matrix	*new_transform;

	transform_update = NULL;
	if (keycode == KEY_I)
		transform_update = translation(0, step, 0);
	else if (keycode == KEY_K)
		transform_update = translation(0, -step, 0);
	else if (keycode == KEY_J)
		transform_update = translation(-step, 0, 0);
	else if (keycode == KEY_SEMICOLON)
		transform_update = translation(step, 0, 0);
	else if (keycode == KEY_U)
		transform_update = translation(0, 0, step);
	else if (keycode == KEY_M)
		transform_update = translation(0, 0, -step);
	if (!transform_update)
		return ;
	new_transform = matrix_product(transform_update, obj->transform);
	set_transform(obj, new_transform);
	free_matrix(transform_update);
	printf("\n=== Object Translated ===\n");
	print_object_info(obj);
	*needs_rerender = true;
}

static void	apply_rotation(t_object *obj, int keycode, bool *needs_rerender)
{
	t_matrix	*transform_update;
	t_matrix	*new_transform;

	transform_update = NULL;
	if (keycode == KEY_I)
		transform_update = rotation_x(0.1);
	else if (keycode == KEY_K)
		transform_update = rotation_x(-0.1);
	else if (keycode == KEY_J)
		transform_update = rotation_y(-0.1);
	else if (keycode == KEY_SEMICOLON)
		transform_update = rotation_y(0.1);
	else if (keycode == KEY_U)
		transform_update = rotation_z(0.1);
	else if (keycode == KEY_M)
		transform_update = rotation_z(-0.1);
	if (!transform_update)
		return ;
	new_transform = matrix_product(obj->transform, transform_update);
	set_transform(obj, new_transform);
	free_matrix(transform_update);
	printf("\n=== Object Rotated ===\n");
	print_object_info(obj);
	*needs_rerender = true;
}

void	handle_object_transform_rotation(int keycode, t_scene *scene,
		bool *needs_rerender)
{
	t_object	*obj;
	double		step;

	if (!scene->selected_object || !scene->selected_object->data)
		return ;
	if (!scene->translation_mode && !scene->rotation_mode)
		return ;
	obj = (t_object *)scene->selected_object->data;
	step = 0.5;
	if (scene->translation_mode)
		apply_translation(obj, keycode, step, needs_rerender);
	else if (scene->rotation_mode && obj->type != SPHERE)
		apply_rotation(obj, keycode, needs_rerender);
	else if (scene->rotation_mode && obj->type == SPHERE)
		printf("\nSpheres cannot be rotated.\n");
}

void	handle_object_controls(int keycode, t_scene *scene,
		bool *needs_rerender)
{
	t_object	*obj;

	if (!scene->selected_object || !scene->selected_object->data)
		return ;
	if (keycode == KEY_O && scene->objects)
	{
		cycle_object_selection(scene, needs_rerender);
		return ;
	}
	obj = (t_object *)scene->selected_object->data;
	if (obj->type == SPHERE)
		resize_sphere(obj, keycode, needs_rerender);
	else if (obj->type == CYLINDER)
	{
		if (keycode == KEY_COMMA || keycode == KEY_DOT)
			resize_cylinder_diameter(obj, keycode, needs_rerender);
		else if (keycode == KEY_H || keycode == KEY_G)
			resize_cylinder_height(obj, keycode, needs_rerender);
	}
}
