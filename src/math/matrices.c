/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:20:13 by jhualves          #+#    #+#             */
/*   Updated: 2025/09/05 17:05:24 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_matrix	*create_matrix(double collum, double row)
{
	t_matrix	*matrix;
	double		**mtx;
	doube		i;

	i = row;
	matrix = safe_malloc(sizeof(t_matrix));
	mtx = safe_malloc(sizeof(double *) * row);
	while (i > 0)
	{
		mtx[i] = safe_malloc(sizeof(double) * collum);
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
	double		i;
	double		j;
	double		k;

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
				product[i][j] += a[i][k] * b[k][j];
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
	final[0][1] = tuple->x;
	final[0][2] = tuple->y;
	final[0][3] = tuple->z;
	final[0][4] = tuple->w;
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
				final[i][j] = 1;
			else
				final[i][j] = 0;
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
			final[j][i] = a[i][j];
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