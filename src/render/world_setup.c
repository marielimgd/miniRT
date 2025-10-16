/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:43:49 by marieli           #+#    #+#             */
/*   Updated: 2025/10/16 14:48:29 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	*create_world(void)
{
	t_scene	*world;

	world = safe_malloc(sizeof(t_scene), ALLOC_TYPE_SCENE);
	world->lights = NULL;
	world->objects = NULL;
	world->selected_object = NULL;
	world->has_ambient = false;
	world->has_camera = false;
	world->translation_mode = false;
	world->rotation_mode = false;
	return (world);
}
