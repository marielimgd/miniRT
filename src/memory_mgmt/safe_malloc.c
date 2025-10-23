/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:22:04 by jhualves          #+#    #+#             */
/*   Updated: 2025/10/22 21:28:00 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/minirt.h"

t_allocation	**get_alloc_head(void)
{
	static t_allocation	*head = NULL;

	return (&head);
}

void	*safe_malloc(size_t size, t_alloc_type u_type)
{
	t_allocation	**head;
	t_allocation	*new_alloc;

	new_alloc = malloc(sizeof(t_allocation));
	if (!new_alloc)
		return (print_error("malloc error"), NULL);
	new_alloc->ptr = malloc(size);
	if (!new_alloc->ptr)
	{
		free(new_alloc);
		return (print_error("malloc error"), NULL);
	}
	new_alloc->type = u_type;
	head = get_alloc_head();
	new_alloc->next = *head;
	*head = new_alloc;
	return (new_alloc->ptr);
}

void	free_all(void)
{
	t_allocation	**head;
	t_allocation	*alloc;
	t_allocation	*next;

	head = get_alloc_head();
	alloc = *head;
	while (alloc)
	{
		next = alloc->next;
		if (alloc->type == ALLOC_TYPE_MTX)
			free_matrix(alloc->ptr);
		else if (alloc->type == ALLOC_TYPE_OBJECT)
			free_object(alloc->ptr);
		else if (alloc->type == ALLOC_TYPE_LIGHT)
			free_light(alloc->ptr);
		else if (alloc->type == ALLOC_TYPE_SCENE)
			free_scene((t_scene *)alloc->ptr);
		else if (alloc->type == ALLOC_TYPE_STRING
			|| alloc->type == ALLOC_TYPE_GENERIC)
			free(alloc->ptr);
		free(alloc);
		alloc = next;
	}
	*head = NULL;
}
