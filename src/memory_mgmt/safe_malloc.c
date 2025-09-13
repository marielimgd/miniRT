/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:22:04 by jhualves          #+#    #+#             */
/*   Updated: 2025/09/13 19:50:41 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_allocation	*get_alloc()
{
	static t_allocation	*alloc;

	return (alloc);
}

void	*safe_malloc(size_t size, t_alloc_type u_type)
{
	t_allocation	*alloc;

	alloc = get_alloc();
	while (alloc)
		alloc = alloc->next;
	alloc = malloc(sizeof(t_allocation));
	if (!alloc)
		return (print_error("malloc error"), NULL);
	alloc->ptr = malloc(size);
	if (!alloc->ptr)
		return (print_error("malloc error"), NULL);
	alloc->type = u_type;
	alloc->next = NULL;
	return (alloc->ptr);
} 
void	free_all(void) // colocar todas as structs que a gente malloca
{
	t_allocation	*alloc;
	t_allocation	*next;

	alloc = get_alloc();
	while (alloc)
	{
		next = alloc->next;
		if (alloc->type == ALLOC_TYPE_MTX)
			free_matrix(alloc->ptr);
		else if (alloc->type == ALLOC_TYPE_STRING || alloc->type == ALLOC_TYPE_GENERIC)
			free(alloc->ptr);
		alloc->ptr = NULL;
		free(alloc);
		alloc = NULL;
		alloc = next;
	}
}

void	free_matrix(t_matrix *m)
{
	int	i;

	i = 0;
	while (i < m->row)
	{
		free(m->matrix[i]);
		i++;
	}
	free(m->matrix);
	free(m);
}

void	free_object(void *obj_ptr)
{
	t_object *obj;

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

void	free_scene(t_scene *scene)
{
	if (scene->lights)
		ft_lstclear(&scene->lights, free);
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
}