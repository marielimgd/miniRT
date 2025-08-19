/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:10:26 by mmariano          #+#    #+#             */
/*   Updated: 2025/08/19 12:54:40 by mmariano         ###   ########.fr       */
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

typedef struct s_scene
{
	double		ambient_light; //ambient light intensity
	t_color		ambient_color; // Ambient light color
	t_camera	camera;
	t_list		*lights; 
	t_list		*objects;
	int			has_ambient; // Flag to check if ambient light is set
}               t_scene;

typedef struct s_light
{
    t_vector    origin;
    double  	brightness;
    t_color 	color;
    t_list		*next; //from libft list pointer
} 				t_light;

typedef enum e_object_type
{
    SPHERE,
    PLANE,
    CYLINDER
}               t_object_type;


typedef struct s_object
{
    t_object_type	type;
    t_vector		origin;
    t_color			color;
    union
    {
        double		diameter;   //Sphere
        t_vector	normal;     //plane
        struct //cylinder properties
		{
            t_vector	orientation;
            double		diameter;
            double		height;
        } 			cylinder;
    };
    struct s_object *next; // To create a linked list
} 				t_object;

#endif