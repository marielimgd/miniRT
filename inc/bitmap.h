/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:18:38 by jhualves          #+#    #+#             */
/*   Updated: 2025/10/23 15:18:38 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMAP_H
# define BITMAP_H

# include "minirt.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdint.h>

# define FILE_HEADER_SIZE 14
# define INFO_HEADER_SIZE 40
# define HEADER_SIZE 54

# pragma pack(push, 1)

typedef struct s_bmp_file_header
{
	uint16_t	type;
	uint32_t	size;
	uint16_t	reserved1;
	uint16_t	reserved2;
	uint32_t	offset;
}				t_bmp_file_header;

typedef struct s_bmp_info_header
{
	uint32_t	size;
	int32_t		width;
	int32_t		height;
	uint16_t	planes;
	uint16_t	bpp;
	uint32_t	compression;
	uint32_t	image_size;
	int32_t		x_pixels_per_meter;
	int32_t		y_pixels_per_meter;
	uint32_t	colors_used;
	uint32_t	colors_important;
}				t_bmp_info_header;

# pragma pack(pop)

void	export_to_bitmap(char *filename, t_scene *scene);
void	validate_scene(t_scene *scene);
void	validate_filename(char *filename);
void	export_bmp(t_scene *world);
#endif