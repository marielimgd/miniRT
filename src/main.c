#include "minirt.h"

static void	init_scene(t_scene *scene)
{
	scene->ambient_light = -1.0;
	scene->has_ambient = false;
	scene->lights = NULL;
	scene->objects = NULL;
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
		parse_error("Usage: ./miniRT <scene.rt>");

	init_scene(&scene);
	parse_scene(argv[1], &scene);
	init_window(&scene);
	render_scene(&scene);
	mlx_loop(scene.mlx.mlx_ptr);

	return (0);
}