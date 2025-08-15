#include "tuple.h"
#include "canvas.h"

t_tuple color(float r, float g, float b)
{
   t_tuple result = {r, g, b, 0.0f};
   return (result);
}

// In main.c

void test_color_operations() 
{
    printf("Running test: Color operations\n");

    // Test adding colors
    t_tuple c1 = color(0.9f, 0.6f, 0.75f);
    t_tuple c2 = color(0.7f, 0.1f, 0.25f);
    t_tuple expected_add = color(1.6f, 0.7f, 1.0f);
    check(are_tuples_equal(add_tuples(c1, c2), expected_add), "Adding colors");

    // Test subtracting colors
    t_tuple expected_sub = color(0.2f, 0.5f, 0.5f);
    check(are_tuples_equal(subtract_tuples(c1, c2), expected_sub), "Subtracting colors");

    // Test multiplying a color by a scalar
    t_tuple c = color(0.2f, 0.3f, 0.4f);
    t_tuple expected_scalar = color(0.4f, 0.6f, 0.8f);
    check(are_tuples_equal(multiply_scalar(c, 2.0f), expected_scalar), "Multiplying by scalar");

    // Test multiplying colors (blending)
    t_tuple c3 = color(1.0f, 0.2f, 0.4f);
    t_tuple c4 = color(0.9f, 1.0f, 0.1f);
    t_tuple expected_blend = color(0.9f, 0.2f, 0.04f);
    check(are_tuples_equal(multiply_tuple(c3, c4), expected_blend), "Multiplying (blending) colors");
}