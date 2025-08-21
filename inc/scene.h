/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:10:26 by mmariano          #+#    #+#             */
/*   Updated: 2025/08/21 18:29:11 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

#include "libft.h"
#include <stdbool.h> //for true/false
#include <stdio.h> //for printf
#include <assert.h> //for assert
#include <math.h> //for math functions
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
    t_vector	orientation;
    int			fov; //field of view (FOV) in degrees
}               t_camera;

typedef struct s_light
{
    t_vector    origin;
    double  	brightness;
    t_color 	color;
} 				t_light;

typedef enum e_object_type
{
    SPHERE,
    PLANE,
    CYLINDER
}               t_object_type;

typedef struct s_cylinder_prop
{
    t_vector    orientation;
    double      diameter;
    double      height;
}               t_cylinder_prop;

typedef union           u_object_properties
{
    double              diameter;
    t_vector            normal;
    t_cylinder_prop     cylinder; 
}                       t_object_properties;

typedef struct s_object
{
    t_object_type       type;
    t_vector            origin;
    t_color             color;
    t_object_properties prop; // Use the named union here
}                       t_object;

typedef struct s_scene
{
	double		ambient_light; //ambient light intensity
	t_color		ambient_color; // Ambient light color
	t_camera	camera;
	t_list		*lights; 
	t_list		*objects;
	int			has_ambient; // Flag to check if ambient light is already set
}               t_scene;

#endif