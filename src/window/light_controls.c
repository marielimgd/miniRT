/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 19:00:00 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/16 19:05:41 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	adjust_light_brightness(t_light *light, int keycode,
		bool *needs_rerender)
{
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

void	handle_light_controls(int keycode, t_scene *scene,
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
	adjust_light_brightness(light, keycode, needs_rerender);
}

static void	move_light(t_light *light, int keycode, double step)
{
	if (keycode == KEY_I)
		light->origin.y += step;
	else if (keycode == KEY_K)
		light->origin.y -= step;
	else if (keycode == KEY_J)
		light->origin.x -= step;
	else if (keycode == KEY_SEMICOLON)
		light->origin.x += step;
	else if (keycode == KEY_U)
		light->origin.z += step;
	else if (keycode == KEY_M)
		light->origin.z -= step;
}

void	handle_light_transform(int keycode, t_scene *scene,
		bool *needs_rerender)
{
	t_light	*light;
	double	step;
	int		old_keycode;

	if (!scene->selected_light || !scene->selected_light->data)
		return ;
	if (!scene->translation_mode)
		return ;
	light = (t_light *)scene->selected_light->data;
	step = 0.5;
	old_keycode = keycode;
	move_light(light, keycode, step);
	if (old_keycode != KEY_I && old_keycode != KEY_K
		&& old_keycode != KEY_J && old_keycode != KEY_SEMICOLON
		&& old_keycode != KEY_U && old_keycode != KEY_M)
		return ;
	printf("\n=== Light Translated ===\n");
	printf("Light Position: (%.1f, %.1f, %.1f)\n",
		light->origin.x, light->origin.y, light->origin.z);
	*needs_rerender = true;
}
