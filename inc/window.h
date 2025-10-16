#ifndef WINDOW_H
# define WINDOW_H

# include "minirt.h"

// --- Window Functions ---
void		init_window(struct s_scene *scene);
int			close_window(struct s_scene *scene);
int			handle_keypress(int keycode, struct s_scene *scene);
void		validate_scene(struct s_scene *scene);
void		validate_filename(char *filename);
void		export_bmp(struct s_scene *world);
void		print_initial_object_selection(struct s_scene *scene);

#endif