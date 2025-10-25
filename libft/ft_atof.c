/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:25:12 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/25 15:07:51 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "libft.h"

static double	calculate_integer_part(const char **str)
{
	double	integer_part;

	integer_part = 0.0;
	while (ft_isdigit(**str))
	{
		integer_part = integer_part * 10.0 + (**str - '0');
		(*str)++;
	}
	return (integer_part);
}

static double	calculate_fractional_part(const char **str)
{
	double	fractional_part;
	double	power_of_10;

	fractional_part = 0.0;
	power_of_10 = 1.0;
	if (**str == '.')
	{
		(*str)++;
		while (ft_isdigit(**str))
		{
			power_of_10 /= 10.0;
			fractional_part = fractional_part + (**str - '0') * power_of_10;
			(*str)++;
		}
	}
	return (fractional_part);
}

double	ft_atof(const char *str)
{
	double	result;
	int		sign;

	result = 0.0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	result = calculate_integer_part(&str);
	result += calculate_fractional_part(&str);
	return (result * sign);
}
