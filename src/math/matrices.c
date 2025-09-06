/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:20:13 by jhualves          #+#    #+#             */
/*   Updated: 2025/09/05 20:09:28 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_matrix	*create_matrix(double collum, double row)
{
	t_matrix	*matrix;
	double		**mtx;
	int			i;

	i = row;
	matrix = safe_malloc(sizeof(t_matrix), ALLOC_TYPE_MTX);
	mtx = safe_malloc(sizeof(double *) * row, ALLOC_TYPE_MTX);
	while (i > 0)
	{
		mtx[i] = safe_malloc(sizeof(double) * collum, ALLOC_TYPE_MTX);
		i--;
	}
	matrix->collum = collum;
	matrix->row = row;
	matrix->matrix = mtx;
	return (matrix);
}

t_matrix	*matrix_product(t_matrix *a, t_matrix *b)
{
	t_matrix	*product;
	int			i;
	int			j;
	int			k;

	if (a->collum != b->row)
		print_error("Wrong values for matrix product");
	i = 0;
	product = create_matrix(a->collum, b->row);
	while (i < a->row)
	{
		j= 0;
		while (j < b->collum)
		{
			k = 0;
			while (k < a->collum)
			{
				product->matrix[i][j] += a->matrix[i][k] * b->matrix[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (product);
}

t_matrix	*tuple_to_matrix(t_vector *tuple)
{
	t_matrix	*final;

	final = create_matrix(1, 4);
	final->matrix[0][1] = tuple->x;
	final->matrix[0][2] = tuple->y;
	final->matrix[0][3] = tuple->z;
	final->matrix[0][4] = tuple->w;
	return (final);
}

t_matrix	*indenty_matrix(double	size)
{
	t_matrix	*final;
	int			i;
	int			j;

	final = create_matrix(size, size);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (i == j)
				final->matrix[i][j] = 1;
			else
				final->matrix[i][j] = 0;
			j++;
		}
		i++;
	}
	return (final);
}

t_matrix	*transpose_matrix(t_matrix *a)
{
	t_matrix	*final;
	int			i;
	int			j;

	final = create_matrix(a->row, a->collum);
	i = 0;
	while (i < a->collum)
	{
		j = 0;
		while (j < a->row)
		{
			final->matrix[j][i] = a->matrix[i][j];
			j++;
		}
		i++;
	}
	return (final);
}

t_matrix	*inverse_matrix(t_matrix *a)
{
	t_matrix	*final;

	if (a->row != a->collum)
		print_error("Trying to inverse non quadratic matrix");
	
	
}