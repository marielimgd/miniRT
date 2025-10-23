/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:20:13 by jhualves          #+#    #+#             */
/*   Updated: 2025/10/22 20:37:45 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minirt.h"

t_matrix	*create_matrix(double collum, double row)
{
	t_matrix	*matrix;
	double		**mtx;
	int			i;

	i = 0;
	matrix = malloc(sizeof(t_matrix));
	mtx = malloc(sizeof(double *) * row);
	while (i < row)
	{
		mtx[i] = malloc(sizeof(double) * collum);
		i++;
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
	product = create_matrix(b->collum, a->row);
	i = -1;
	while (++i < a->row)
	{
		j = -1;
		while (++j < b->collum)
		{
			product->matrix[i][j] = 0;
			k = -1;
			while (++k < a->collum)
				product->matrix[i][j] += a->matrix[i][k] * b->matrix[k][j];
		}
	}
	return (product);
}

t_matrix	*tuple_to_matrix(t_vector *tuple)
{
	t_matrix	*final;

	final = create_matrix(1, 4);
	final->matrix[0][0] = tuple->x;
	final->matrix[1][0] = tuple->y;
	final->matrix[2][0] = tuple->z;
	final->matrix[3][0] = tuple->w;
	return (final);
}

t_matrix	*identity_matrix(void)
{
	t_matrix	*final;
	int			i;
	int			j;

	final = create_matrix(4, 4);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
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
