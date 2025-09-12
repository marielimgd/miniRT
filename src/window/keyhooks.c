/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:55:31 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/12 18:17:27 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


int	handle_keypress(int keycode, t_scene *scene)
{
	bool	needs_rerender;

	needs_rerender = false;
	if (keycode == ESC_KEY)
		close_window(scene);
	else if (keycode == PLUS_KEY)
	{
		scene->camera.fov -= 5;
		if (scene->camera.fov < 1)
			scene->camera.fov = 1;
		needs_rerender = true;
	}
	else if (keycode == MINUS_KEY)
	{
		scene->camera.fov += 5;
		if (scene->camera.fov > 179)
			scene->camera.fov = 179;
		needs_rerender = true;
	}
	if (needs_rerender)
		render_scene(scene);
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
