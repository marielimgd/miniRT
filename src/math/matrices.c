/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:20:13 by jhualves          #+#    #+#             */
/*   Updated: 2025/09/05 16:02:58 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_matrix	*create_matrix(int collum, int row)
{
	t_matrix	*matrix;
	int			**mtx;
	int			i;

	i = row;
	matrix = safe_malloc(sizeof(t_matrix));
	mtx = safe_malloc(sizeof(int *) * row);
	while (i > 0)
	{
		mtx[i] = safe_malloc(sizeof(int) * collum);
		i--;
	}
	matrix->collum = collum;
	matrix->row = row;
	matrix->matrix = mtx;
	return (matrix);
}

t_matrix	*matrix_product(t_matrix *a; t_matrix *b)
{
	t_matrix	*product;
	
	if (a->collum != b->row)
	{
		print_error("Wrong values for matrix product");
		EXIT_FAILURE;
	}
	product = create_matrix(a->collum, b->row);
	
	
	
}