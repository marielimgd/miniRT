/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:41:51 by marieli           #+#    #+#             */
/*   Updated: 2025/09/11 20:48:28 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	simple_rand(void)
{
	static unsigned int	seed;
    
    seed = 0xDEADBEEF;

	seed = (1103515245 * seed + 12345);
	return ((unsigned int)(seed / 65536) % 32768);
}

void	randomize_object_colors(t_scene *scene)
{
	t_list	*current_obj;

	current_obj = scene->objects;
	while (current_obj)
	{
		t_object *obj = (t_object *)current_obj->data;
		obj->material.color.r = simple_rand() % 256;
		obj->material.color.g = simple_rand() % 256;
		obj->material.color.b = simple_rand() % 256;
		obj->color = obj->material.color;
		current_obj = current_obj->next;
	}
}
