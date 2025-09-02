#include "minirt.h"

void	render_scene(t_scene *scene)
{
	int	x;
	int	y;

	ft_printf("Parsing complete. Drawing test window...\n");
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(&scene->mlx, x, y, (t_color){0, 0, 255});
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr,
		scene->mlx.img_ptr, 0, 0);
}
