#include "tuple.h"

t_tuple negate_tuple(t_tuple tuple)
{
    t_tuple result = {-tuple.x, 
					-tuple.y, 
					-tuple.z, 
					-tuple.w};
    return (result);
}

t_tuple multiply_tuple(t_tuple a, t_tuple b) 
{
    t_tuple result = { a.x * b.x, 
                    a.y * b.y, 
                    a.z * b.z, 
                    a.w * b.w };
    return (result);
}

t_tuple multiply_scalar(t_tuple tuple, float scalar)
{
    t_tuple result = {tuple.x * scalar, 
                      tuple.y * scalar, 
                      tuple.z * scalar, 
                      tuple.w * scalar};
    return (result);
}

t_tuple divide_tuple(t_tuple tuple, float scalar)
{
    if (fabs(scalar) < EPSILON)
    {
        fprintf(stderr, "Error: Division by zero\n");
        exit(EXIT_FAILURE);
    }
   t_tuple result = {tuple.x / scalar, 
                     tuple.y / scalar, 
                     tuple.z / scalar, 
                     tuple.w / scalar};
   return (result);
}

t_tuple add_tuples(t_tuple a, t_tuple b)
{
   t_tuple result = {a.x + b.x, 
						a.y + b.y, 
						a.z + b.z, 
						a.w + b.w};
   return (result);
}
t_tuple subtract_tuples(t_tuple a, t_tuple b)
{
    return (create_tuple(a.x - b.x, 
						a.y - b.y, 
						a.z - b.z, 
						a.w - b.w));
}
float tuple_magnitude(t_tuple tuple)
{
	    return (sqrtf(
        tuple.x * tuple.x +
        tuple.y * tuple.y +
        tuple.z * tuple.z +
        tuple.w * tuple.w));
}

t_tuple tuple_normalize(t_tuple t) 
{
    float mag = tuple_magnitude(t);

    t_tuple result = {
        t.x / mag,
        t.y / mag,
        t.z / mag,
        t.w / mag  
    };
    return (result);
}

float tuple_dot_product(t_tuple a, t_tuple b) 
{
    return (a.x * b.x +
            a.y * b.y +
            a.z * b.z +
            a.w * b.w);
}

t_tuple tuple_cross_product(t_tuple a, t_tuple b) 
{
    t_tuple result = {a.y * b.z - a.z * b.y,
              a.z * b.x - a.x * b.z,
              a.x * b.y - a.y * b.x,
              0};
    return (result);
}