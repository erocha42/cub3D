#ifndef CUB3D_H
# define CUB3D_H

# include "getnextline/get_next_line.h"
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		screen;
	char		*n_path;
	char		*s_path;
	char		*w_path;
	char		*e_path;
	t_img		tex_n;
	t_img		tex_s;
	t_img		tex_w;
	t_img		tex_e;
	int			ground_color;
	int			ceiling_color;
	char		**map;
	int			map_width;
	int			map_height;

	t_player	player;
}				t_game;

int				init_mlx(t_game *game);
int				checking(char *av[]);

#endif