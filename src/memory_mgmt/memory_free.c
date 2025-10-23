/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 19:30:00 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/22 21:05:09 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

void	free_matrix(t_matrix *m)
{
	int	i;

	if (!m)
		return ;
	if (m->matrix)
	{
		i = 0;
		while (i < m->row)
		{
			if (m->matrix[i])
				free(m->matrix[i]);
			i++;
		}
		free(m->matrix);
	}
	free(m);
}

void	free_object(void *obj_ptr)
{
	t_object	*obj;

	obj = (t_object *)obj_ptr;
	if (obj)
	{
		if (obj->transform)
			free_matrix(obj->transform);
		if (obj->inverse_transform)
			free_matrix(obj->inverse_transform);
		if (obj->transpose_inverse_transform)
			free_matrix(obj->transpose_inverse_transform);
		free(obj);
	}
}

void	free_light(void *light_ptr)
{
	t_light	*light;

	light = (t_light *)light_ptr;
	if (light)
		free(light);
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->camera.transform)
		free_matrix(scene->camera.transform);
	if (scene->lights)
		ft_lstclear(&scene->lights, free_light);
	if (scene->objects)
		ft_lstclear(&scene->objects, free_object);
	if (scene->mlx.img_ptr)
		mlx_destroy_image(scene->mlx.mlx_ptr, scene->mlx.img_ptr);
	if (scene->mlx.win_ptr)
		mlx_destroy_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	if (scene->mlx.mlx_ptr)
	{
		mlx_destroy_display(scene->mlx.mlx_ptr);
		free(scene->mlx.mlx_ptr);
	}
	free(scene);
}

void	print_error(char *s)
{
	printf("\033[1;31m%s\033[0m\n", s);
	free_all();
	EXIT_FAILURE;
}
