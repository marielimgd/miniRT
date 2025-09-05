/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:22:04 by jhualves          #+#    #+#             */
/*   Updated: 2025/09/05 19:40:31 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_allocation	*get_alloc()
{
	static t_allocation	alloc;
	
	return (&alloc);
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
			//free_matrix(alloc->ptr);
			free(alloc->ptr);
		else if (alloc->type == ALLOC_TYPE_STRING || alloc->type == ALLOC_TYPE_GENERIC)
			free(alloc->ptr);
		alloc->ptr = NULL;
		free(alloc);
		alloc = NULL;
		alloc = next;
	}
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
