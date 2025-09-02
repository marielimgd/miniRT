#ifndef WINDOW_H
# define WINDOW_H

# include "minirt.h"

// --- Window Functions ---
void		init_window(struct s_scene *scene);
int			close_window(struct s_scene *scene);
int			handle_keypress(int keycode, struct s_scene *scene);

#endif