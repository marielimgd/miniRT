/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:17:26 by mmariano          #+#    #+#             */
/*   Updated: 2025/09/13 17:12:40 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	process_pixel(t_scene *scene, int x, int y)
{
	t_ray	ray;
	t_color	pixel_color;



	ray = ray_for_pixel(&scene->camera, x, y);


	t_intersection_list	intersections;
	t_intersection		*hit;
	printf("\n--- DEBUGGING CENTER PIXEL ---\n");
	printf("1. Ray Generated:\n");
	printf("   Origin:    (%.2f, %.2f, %.2f)\n", ray.origin.x,
		ray.origin.y, ray.origin.z);
	printf("   Direction: (%.2f, %.2f, %.2f)\n", ray.direction.x,
		ray.direction.y, ray.direction.z);
	
	intersections = intersect_world(scene, ray);
	printf("2. Intersections Found: %d\n", intersections.count);

	hit = find_hit(&intersections);
	if (hit != NULL)
		printf("3. Closest Hit Found at t = %.2f\n", hit->t);
	else
		printf("3. No valid hit was found.\n");
	printf("----------------------------\n");
		
	pixel_color = color_at(scene, ray);
	my_mlx_pixel_put(&scene->mlx, x, y, pixel_color);
}


static void	*render_thread(void *thread_arg)
{
	t_thread_data	*data;
	int				x;
	int				y;

	data = (t_thread_data *)thread_arg;
	y = data->start_row;
	while (y < data->end_row)
	{
		x = 0;
		while (x < WIDTH)
		{
			process_pixel(data->scene, x, y);
			x++;
		}
		y++;
	}
	return (NULL);
}

static void	launch_threads(pthread_t *threads, t_thread_data *data, t_scene *scene)
{
	int	i;
	int	rows_per_thread;

	rows_per_thread = HEIGHT / NUM_THREADS;
	i = 0;
	while (i < NUM_THREADS)
	{
		data[i].id = i;
		data[i].scene = scene;
		data[i].start_row = i * rows_per_thread;
		if (i == NUM_THREADS - 1)
			data[i].end_row = HEIGHT;
		else
			data[i].end_row = (i + 1) * rows_per_thread;
		pthread_create(&threads[i], NULL, render_thread, &data[i]);
		i++;
	}
}

static void	join_threads(pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void	render_scene(t_scene *scene)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	thread_data[NUM_THREADS];

	launch_threads(threads, thread_data, scene);
	join_threads(threads);
	mlx_put_image_to_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr,
		scene->mlx.img_ptr, 0, 0);
}
