/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:35:30 by marvin            #+#    #+#             */
/*   Updated: 2025/10/23 12:37:02 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef MULTITHREADING_H
# define MULTITHREADING_H
# include "minirt.h"
# include <pthread.h>

# define NUM_THREADS 8

typedef struct s_thread_data
{
	int			id;
	int			start_row;
	int			end_row;
	t_scene		*scene;
}				t_thread_data;

#endif