/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 19:00:00 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/16 19:05:41 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_camera_transform(t_camera *cam)
{
	t_vector	to;

	if (cam->transform)
		free_matrix(cam->transform);
	normalization(&cam->orientation, &cam->orientation);
	if (fabs(cam->orientation.y) > 0.999)
		cam->up = create_vector(0, 0, 1);
	else
		cam->up = create_vector(0, 1, 0);
	add_tuples(&to, &cam->from, &cam->orientation);
	cam->transform = view_transform(cam->from, to, cam->up);
}

void	handle_camera_controls(int keycode, t_scene *scene,
		bool *needs_rerender)
{
	t_vector	right;

	if (keycode == KEY_W)
		add_tuples(&scene->camera.from, &scene->camera.from,
			&scene->camera.orientation);
	else if (keycode == KEY_S)
		subtract_tuples(&scene->camera.from, &scene->camera.from,
			&scene->camera.orientation);
	else if (keycode == KEY_A)
	{
		dot_cross(&right, &scene->camera.orientation, &scene->camera.up);
		subtract_tuples(&scene->camera.from, &scene->camera.from, &right);
	}
	else if (keycode == KEY_D)
	{
		dot_cross(&right, &scene->camera.orientation, &scene->camera.up);
		add_tuples(&scene->camera.from, &scene->camera.from, &right);
	}
	else
		return ;
	*needs_rerender = true;
}

void	handle_camera_rotation(int keycode, t_scene *scene,
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
