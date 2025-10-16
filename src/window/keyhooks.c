/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:55:31 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/16 19:38:57 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	toggle_translation_mode(t_scene *scene)
{
	scene->translation_mode = !scene->translation_mode;
	scene->rotation_mode = false;
	if (scene->translation_mode)
		printf("\n=== Translation Mode: ON ===\n");
	else
		printf("\n=== Translation Mode: OFF ===\n");
	if (scene->translation_mode)
		printf("Use I/K (Y), J/; (X), U/M (Z)"
			" to translate selected object/light\n");
}

static void	toggle_rotation_mode(t_scene *scene)
{
	scene->rotation_mode = !scene->rotation_mode;
	scene->translation_mode = false;
	if (scene->rotation_mode)
		printf("\n=== Rotation Mode: ON ===\n");
	else
		printf("\n=== Rotation Mode: OFF ===\n");
	if (scene->rotation_mode)
		printf("Use I/K (X-axis), J/; (Y-axis), U/M (Z-axis)"
			" to rotate selected object\n");
}

static void	handle_all_controls(int keycode, t_scene *scene,
		bool *needs_rerender)
{
	handle_object_transform_rotation(keycode, scene, needs_rerender);
	handle_light_transform(keycode, scene, needs_rerender);
	handle_camera_controls(keycode, scene, needs_rerender);
	handle_object_controls(keycode, scene, needs_rerender);
	handle_camera_rotation(keycode, scene, needs_rerender);
	handle_light_controls(keycode, scene, needs_rerender);
}

int	handle_keypress(int keycode, t_scene *scene)
{
	bool	needs_rerender;

	needs_rerender = false;
	if (keycode == ESC_KEY)
		close_window(scene);
	if (keycode == KEY_T)
	{
		toggle_translation_mode(scene);
		return (0);
	}
	if (keycode == KEY_R)
	{
		toggle_rotation_mode(scene);
		return (0);
	}
	handle_all_controls(keycode, scene, &needs_rerender);
	if (needs_rerender)
	{
		update_camera_transform(&scene->camera);
		render_scene(scene);
	}
	return (0);
}

int	handle_mouse_scroll(int button, int x, int y, t_scene *scene)
{
	double	step;

	(void)x;
	(void)y;
	step = 5.0 * (M_PI / 180.0);
	if (button == MOUSE_SCROLL_UP)
	{
		scene->camera.fov -= step;
		if (scene->camera.fov < 1.0 * (M_PI / 180.0))
			scene->camera.fov = 1.0 * (M_PI / 180.0);
		camera_init(&scene->camera, WIDTH, HEIGHT, scene->camera.fov);
		update_camera_transform(&scene->camera);
		render_scene(scene);
	}
	else if (button == MOUSE_SCROLL_DOWN)
	{
		scene->camera.fov += step;
		if (scene->camera.fov > 179.0 * (M_PI / 180.0))
			scene->camera.fov = 179.0 * (M_PI / 180.0);
		camera_init(&scene->camera, WIDTH, HEIGHT, scene->camera.fov);
		update_camera_transform(&scene->camera);
		render_scene(scene);
	}
	return (0);
}
