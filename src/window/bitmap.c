/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:09:54 by mmariano          #+#    #+#             */
/*   Updated: 2025/10/15 18:27:05 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	write_file_header(int fd)
{
	t_bmp_file_header	header;

	header.type = 0x4D42;
	header.size = HEADER_SIZE + (WIDTH * HEIGHT * 4);
	header.reserved1 = 0;
	header.reserved2 = 0;
	header.offset = HEADER_SIZE;
	if (write(fd, &header, FILE_HEADER_SIZE) < 0)
		print_error("Failed to write BMP file header");
}

static void	write_info_header(int fd)
{
	t_bmp_info_header	header;

	header.size = INFO_HEADER_SIZE;
	header.width = WIDTH;
	header.height = HEIGHT;
	header.planes = 1;
	header.bpp = 32;
	header.compression = 0;
	header.image_size = WIDTH * HEIGHT * 4;
	header.x_pixels_per_meter = 0;
	header.y_pixels_per_meter = 0;
	header.colors_used = 0;
	header.colors_important = 0;
	if (write(fd, &header, INFO_HEADER_SIZE) < 0)
		print_error("Failed to write BMP info header");
}

static void	write_pixel_data(int fd, t_scene *scene)
{
	int		y;
	int		x;
	int		color;
	char	pixel[4];

	y = HEIGHT - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = *(int *)(scene->mlx.addr + (y * scene->mlx.line_len
				+ x * (scene->mlx.bpp / 8)));
			pixel[0] = (color) & 0xFF;
			pixel[1] = (color >> 8) & 0xFF;
			pixel[2] = (color >> 16) & 0xFF;
			pixel[3] = 0;
			if (write(fd, pixel, 4) < 0)
				print_error("Failed to write BMP pixel data");
			x++;
		}
		y--;
	}
}

void	export_to_bitmap(char *filename, t_scene *scene)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		print_error("Failed to create BMP file");
	write_file_header(fd);
	write_info_header(fd);
	write_pixel_data(fd, scene);
	close(fd);
	printf("Image saved to %s\n", filename);
}
