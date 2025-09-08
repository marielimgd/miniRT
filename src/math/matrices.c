/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:20:13 by jhualves          #+#    #+#             */
/*   Updated: 2025/09/08 17:28:39 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/* t_matrix	*create_matrix(double collum, double row)
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
} */
t_matrix	*create_matrix(double collum, double row)
{
	t_matrix	*matrix;
	int			i;

	matrix = safe_malloc(sizeof(t_matrix), ALLOC_TYPE_MTX);
	matrix->row = row;
	matrix->collum = collum;
	matrix->matrix = safe_malloc(sizeof(double *) * row, ALLOC_TYPE_MTX);
	
	i = 0;
	while (i < row)
	{
		matrix->matrix[i] = safe_malloc(sizeof(double) * collum,
				ALLOC_TYPE_MTX);
		i++;
	}
	return (matrix);
}

/* t_matrix	*matrix_product(t_matrix *a, t_matrix *b)
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
			product->matrix[i][j] = 0;
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
} */

t_matrix	*matrix_product(t_matrix *a, t_matrix *b)
{
	t_matrix	*product;
	int			i;
	int			j;
	int			k;

	if (a->collum != b->row)
		print_error("Wrong values for matrix product");
	product = create_matrix(a->row, b->collum);
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
	final->matrix[0][1] = tuple->x;
	final->matrix[0][2] = tuple->y;
	final->matrix[0][3] = tuple->z;
	final->matrix[0][4] = tuple->w;
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

/* t_matrix	*inverse_matrix(t_matrix *a)
{
	t_matrix	*final;

	final = NULL;

	if (a->row != a->collum)
		print_error("Trying to inverse non quadratic matrix");
	
	return(final);
} */


t_matrix	*translation(double x, double y, double z)
{
	t_matrix	*final;

	final = identity_matrix();
	final->matrix[0][3] = x;
	final->matrix[1][3] = y;
	final->matrix[2][3] = z;
	return (final);
}


t_matrix	*scaling(double x, double y, double z)
{
	t_matrix	*final;

	final = identity_matrix(); 
	final->matrix[0][0] = x;
	final->matrix[1][1] = y;
	final->matrix[2][2] = z;
	return (final);
}


t_vector	multiply_matrix_by_tuple(t_matrix *m, t_vector t)
{
	t_vector	result;

	result.x = m->matrix[0][0] * t.x + m->matrix[0][1] * t.y + m->matrix[0][2] * t.z + m->matrix[0][3] * t.w;
	result.y = m->matrix[1][0] * t.x + m->matrix[1][1] * t.y + m->matrix[1][2] * t.z + m->matrix[1][3] * t.w;
	result.z = m->matrix[2][0] * t.x + m->matrix[2][1] * t.y + m->matrix[2][2] * t.z + m->matrix[2][3] * t.w;
	result.w = m->matrix[3][0] * t.x + m->matrix[3][1] * t.y + m->matrix[3][2] * t.z + m->matrix[3][3] * t.w;
	return (result);
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
}