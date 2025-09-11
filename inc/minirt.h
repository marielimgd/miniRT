#ifndef MINIRT_H
# define MINIRT_H

/* --------------- Libraries ---------------------- */

# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../minilibx-linux/minilibx-linux/mlx.h"

/*--------------Constants----------------------------*/

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define WIDTH 800
# define HEIGHT 800
# define ESC_KEY 65307
# define EPSILON 0.00001

/* -----------------Structs--------------------------*/

struct s_object;
struct s_list;

typedef struct s_vector
{
	double			x;
	double			y;
	double			z;
	double			w; //w=0: vector, w=1: point
}					t_vector;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct s_matrix
{
	double				**matrix;
	double				collum;
	double				row;
}					t_matrix;


// --- Rendering ---
typedef struct s_ray
{
	t_vector		origin;
	t_vector		direction;
}					t_ray;

typedef struct s_hit
{
	double			t;
	struct s_object	*object;
	t_vector		point;
	t_vector		normal;
}					t_hit;

typedef struct s_mlx_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_mlx_data;

// --- Scene Elements ---
typedef struct s_camera
{
	t_vector		origin;
	t_vector		orientation;
	int				fov;
}					t_camera;

typedef struct s_light
{
	t_vector		origin;
	double			brightness;
	t_color			color;
}					t_light;

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER
}					t_object_type;

typedef struct s_sphere_prop
{
	double			radius;
}					t_sphere_prop;

typedef struct s_cylinder_prop
{
	t_vector		orientation;
	double			diameter;
	double			height;
}					t_cylinder_prop;

typedef struct s_plane_prop
{
	t_vector		normal;
}					t_plane_prop;

typedef union u_object_properties
{
	t_sphere_prop	sphere;
	t_cylinder_prop	cylinder;
	t_plane_prop	plane;
}					t_object_properties;

typedef struct s_object
{
	t_object_type		type;
	t_vector			origin;
	t_color				color;
	t_matrix			*transform;
	t_object_properties	prop;
}						t_object;

// --- Intersections ---
typedef struct s_intersection
{
	double				t;
	t_object			*object;
}						t_intersection;

typedef struct s_intersec_list
{
	int				count;
	t_intersection		intersections[10]; //mudar depois
}					t_intersection_list;

// --- Main Scene Struct ---
typedef struct s_scene
{
	double			ambient_light;
	t_color			ambient_color;
	t_camera		camera;
	struct s_list	*lights;
	struct s_list	*objects;
	bool			has_ambient;
	t_mlx_data		mlx;
}					t_scene;


// --- Safe Allocation ---

typedef enum e_alloc_type
{
	ALLOC_TYPE_GENERIC,
	ALLOC_TYPE_MTX,
	ALLOC_TYPE_STRING,
}			t_alloc_type;

typedef struct s_allocation
{
	t_alloc_type	type;
	void			*ptr;
	struct s_allocation	*next;
}	t_allocation;


# include "parser.h"
# include "window.h"
# include "raytracer.h"

#endif