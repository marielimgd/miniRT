#ifndef TUPLE_H
#define TUPLE_H

#include <stdbool.h> //for true/false
#include <stdio.h> //for printf
#include <assert.h> //for assert
#include <math.h> //for math functions
#include <stdlib.h> //for atof
#include <fcntl.h>

#define EPSILON 0.00001 

typedef struct s_tuple
{
    float x;
    float y;
    float z;
    float w; //0 for point, 1 for vector
} t_tuple;

#define red x
#define green y
#define blue z

t_tuple    create_tuple(float x, float y, float z, float w);
t_tuple    create_point(float x, float y, float z);
t_tuple    create_vector(float x, float y, float z);
bool       is_point(t_tuple tuple);
bool       is_vector(t_tuple tuple);
bool       are_tuples_equal(t_tuple a, t_tuple b);
t_tuple    add_tuples(t_tuple a, t_tuple b);
t_tuple    subtract_tuples(t_tuple a, t_tuple b);
float      tuple_magnitude(t_tuple tuple);
t_tuple    tuple_normalize(t_tuple t);
float      tuple_dot_product(t_tuple a, t_tuple b);
t_tuple    tuple_cross_product(t_tuple a, t_tuple b);
t_tuple    multiply_scalar(t_tuple tuple, float scalar);
t_tuple    multiply_tuple(t_tuple a, t_tuple b);

#endif