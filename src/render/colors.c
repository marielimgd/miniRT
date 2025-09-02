#include "minirt.h"

void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, t_color color)
{
	char	*dst;
	int		rgb_int;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	rgb_int = (color.r << 16) | (color.g << 8) | color.b;
	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = rgb_int;
}
