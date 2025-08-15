/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:10:26 by mmariano          #+#    #+#             */
/*   Updated: 2025/08/14 19:31:08 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

#include "libft.h"
#include <stdbool.h> //for true/false
#include <stdio.h> //for printf
#include <assert.h> //for assert
#include <math.h> //for math functions
#include <stdlib.h> //for atof
#include <fcntl.h>

typedef struct s_vector
{
    double x;
    double y;
    double z;
}               t_vector;

typedef struct s_color
{
    int r;
    int g;
    int b;
}               t_color;

typedef struct s_camera
{
    t_vector	origin;
    t_vector	direction;
    int			fov; // Field of view in degrees
}               t_camera;

typedef struct s_scene
{
	double		ambient_light; // Ambient light intensity
	t_color		ambient_color; // Ambient light color
	t_camera	camera;
	t_list		*lights; 
	t_list		*objects;
}               t_scene;

#endif