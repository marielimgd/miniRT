#include "tuple.h"

typedef struct 
{
    t_tuple position;
    t_tuple velocity;
} projectile;

typedef struct 
{
    t_tuple gravity;
    t_tuple wind;
} environment;

projectile tick(environment env, projectile proj)
{
    t_tuple new_position = add_tuples(proj.position, proj.velocity);

    t_tuple temp_velocity = add_tuples(proj.velocity, env.gravity);
    t_tuple new_velocity = create_vector(temp_velocity.x, temp_velocity.y, temp_velocity.z);
    projectile new_proj = {new_position, new_velocity};
    return(new_proj);
}

void print_tuple(t_tuple tuple)
{
    printf("(%f, %f, %f)\n", tuple.x, tuple.y, tuple.z);
}

/* int main(void)
{
    printf("Starting projectile simulation...\n");

    t_tuple start_position = create_point(0,1,0);
    t_tuple start_velocity = tuple_normalize(create_vector(1, 1.8, 0));

    start_velocity.x *= 1.25f;
    start_velocity.y *= 1.25f;
    start_velocity.z *= 1.25f;

    projectile proj = {start_position, start_velocity};

    environment env = {create_vector(0, -0.1, 0), 
                        create_vector(0.1, 0, 0)};

    int ticks = 0;
    while (proj.position.y > 0)
    {
        proj = tick(env, proj);
        ticks++;
        printf("Tick %d: Projectile at ", ticks);
        print_tuple(proj.position);
        printf("\n");
    }
    printf("Projectile landed after %d ticks.\n", ticks);
    return(0);
} */