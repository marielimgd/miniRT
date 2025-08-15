#include "tuple.h"

t_tuple create_tuple(float x, float y, float z, float w) 
{
    t_tuple new_tuple;
    new_tuple.x = x;
    new_tuple.y = y;
    new_tuple.z = z;
    new_tuple.w = w;
    return (new_tuple);
}

t_tuple create_point(float x, float y, float z) 
{
    return (create_tuple(x, y, z, 1.0f));
}

t_tuple create_vector(float x, float y, float z) 
{
    return (create_tuple(x, y, z, 0.0f));
}

bool is_point(t_tuple tuple) 
{
    return (tuple.w == 1.0f);
}

bool is_vector(t_tuple tuple) 
{
    return (tuple.w == 0.0f);
}

bool are_tuples_equal(t_tuple a, t_tuple b) 
{
    return (fabs(a.x - b.x) < EPSILON &&
            fabs(a.y - b.y) < EPSILON &&
            fabs(a.z - b.z) < EPSILON &&
            fabs(a.w - b.w) < EPSILON);
}

