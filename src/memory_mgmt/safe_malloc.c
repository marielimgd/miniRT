/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:22:04 by jhualves          #+#    #+#             */
/*   Updated: 2025/09/09 17:55:09 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_allocation	*get_alloc()
{
	static t_allocation	*alloc;

	alloc = NULL;	
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


void	free_all(void)
{
	t_allocation	**list_head;
	t_allocation	*current;
	t_allocation	*next;

	list_head = get_alloc_list();
	current = *list_head;
	while (current)
	{
		next = current->next;
		if (current->ptr)
			free(current->ptr);
		free(current);
		current = next;
	}
	*list_head = NULL;
}

void	free_all(void)
{
	t_allocation	**list_head;
	t_allocation	*current;
	t_allocation	*next;

	list_head = get_alloc_list();
	current = *list_head;
	while (current)
	{
		next = current->next;
		if (current->type == ALLOC_TYPE_MTX)
			free_matrix(current->ptr);
		else
			free(current->ptr);
		free(current);
		current = next;
	}
	*list_head = NULL;
}


void	free_matrix(t_matrix *m)
{
	int	i;

	printf("    -> Attempting to free matrix at address: %p\n", (void *)m);
	if (!m)
		return ;
	i = 0;
	if (m->matrix)
	{
		while (i < m->row)
		{
			printf("        -> Freeing matrix row %d at address: %p\n", i, (void *)m->matrix[i]);
			if (m->matrix[i])
				free(m->matrix[i]);
			i++;
		}
		free(m->matrix);
	}
	free(m);
	printf("    -> Successfully freed matrix at %p\n", (void *)m);
} 