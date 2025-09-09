/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:22:04 by jhualves          #+#    #+#             */
/*   Updated: 2025/09/08 19:39:01 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/* t_allocation	*get_alloc()
{
	static t_allocation	*alloc;

	alloc = NULL;	
	return (&alloc);
} */

/* void	free_all(void) // colocar todas as structs que a gente malloca
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
} */

/* void	*safe_malloc(size_t size, t_alloc_type u_type)
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
} */

#include "minirt.h"

/**
 * @brief Manages a static pointer to the head of the allocation list.
 * This is the correct way to manage a global-like list.
 * @return A pointer to the list's head pointer.
 */
t_allocation	**get_alloc_list(void)
{
	static t_allocation	*head = NULL;

	return (&head);
}

/**
 * @brief Frees all tracked memory allocations.
 */
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

void	*safe_malloc(size_t size, t_alloc_type u_type)
{
	t_allocation	*new_node;
	t_allocation	**list_head;

	new_node = malloc(sizeof(t_allocation));
	if (!new_node)
	{
		free_all();
		print_error("Malloc error on tracking node");
		exit(1);
	}
	new_node->ptr = malloc(size);
	if (!new_node->ptr)
	{
		free(new_node);
		free_all();
		print_error("Malloc error on user pointer");
		exit(1);
	}
	new_node->type = u_type;
	list_head = get_alloc_list();
	new_node->next = *list_head; // New node points to the old head
	*list_head = new_node;      // List head now points to the new node
	return (new_node->ptr);
}