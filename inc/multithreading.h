#ifndef MULTITHREADING_H
#define MULTITHREADING_H

#include "minirt.h"
#include <pthread.h> 

#define NUM_THREADS 8

typedef struct s_thread_data
{
	int			id;
	int			start_row;
	int			end_row;
	t_scene		*scene;
}				t_thread_data;

#endif