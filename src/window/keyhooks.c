/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:55:31 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/15 17:41:33 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	update_camera_transform(t_camera *cam)
{
	t_vector	to;

	if (cam->transform)
		free_matrix(cam->transform);
	normalization(&cam->orientation, &cam->orientation);
	add_tuples(&to, &cam->from, &cam->orientation);
	cam->transform = view_transform(cam->from, to, cam->up);
}

static void	handle_light_controls(int keycode, t_scene *scene,
		bool *needs_rerender)
{
	t_light	*light;

	if (keycode == KEY_L && scene->lights)
	{
		scene->selected_light = scene->selected_light->next;
		if (scene->selected_light == NULL)
			scene->selected_light = scene->lights;
	}
	if (scene->selected_light == NULL)
		return ;
	light = (t_light *)scene->selected_light->data;
	if (keycode == PLUS_KEY)
	{
		light->brightness += 0.1;
		if (light->brightness > 1.0)
			light->brightness = 1.0;
		*needs_rerender = true;
	}
	else if (keycode == MINUS_KEY)
	{
		light->brightness -= 0.1;
		if (light->brightness < 0.0)
			light->brightness = 0.0;
		*needs_rerender = true;
	}
}

static void	handle_camera_controls(int keycode, t_scene *scene,
		bool *needs_rerender)
{
	if (keycode == KEY_W) 
		add_tuples(&scene->camera.from, &scene->camera.from,
			&scene->camera.orientation);
	else if (keycode == KEY_S) 
		subtract_tuples(&scene->camera.from, &scene->camera.from,
			&scene->camera.orientation);
	else if (keycode == KEY_A)
	{
		t_vector right;
		dot_cross(&right, &scene->camera.orientation, &scene->camera.up);
		subtract_tuples(&scene->camera.from, &scene->camera.from, &right);
	}
	else if (keycode == KEY_D) 
	{
		t_vector right;
		dot_cross(&right, &scene->camera.orientation, &scene->camera.up);
		add_tuples(&scene->camera.from, &scene->camera.from, &right);
	}
	else
		return ;
	*needs_rerender = true;
}

static void	handle_camera_rotation(int keycode, t_scene *scene,
		bool *needs_rerender)
{
	t_matrix	*rot_m;

	if (keycode == KEY_LEFT)
		rot_m = rotation_y(0.1);
	else if (keycode == KEY_RIGHT)
		rot_m = rotation_y(-0.1); 
	else if (keycode == KEY_UP)
		rot_m = rotation_x(0.1); 
	else if (keycode == KEY_DOWN)
		rot_m = rotation_x(-0.1); 
	else
		return ;
	scene->camera.orientation = multiply_matrix_by_tuple(rot_m,
			scene->camera.orientation);
	free_matrix(rot_m);
	*needs_rerender = true;
}

int	handle_keypress(int keycode, t_scene *scene)
{
	bool	needs_rerender;

	needs_rerender = false;
	if (keycode == ESC_KEY)
		close_window(scene);
	handle_camera_controls(keycode, scene, &needs_rerender);
	handle_camera_rotation(keycode, scene, &needs_rerender);
	handle_light_controls(keycode, scene, &needs_rerender);
	if (needs_rerender)
	{
		update_camera_transform(&scene->camera);
		render_scene(scene);
	}
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
