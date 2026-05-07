#ifndef CUB3D_H
# define CUB3D_H

# include "getnextline/get_next_line.h"
# include "libft/libft.h"
# include "miniaudio.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_error
{
	NO_ERROR,
	EXTD_ERROR,
	FD_ERROR,
	MALLOC_ERROR,
	MAP_ERROR,
	DATA_ERROR,
	IMG_ERROR
}				t_error;

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
	int			move_up;
	int			move_down;
	int			move_left;
	int			move_right;
	int			rotate_left;
	int			rotate_right;
	int			last_x;
	int			sprint;
	int			torch;
}				t_player;

typedef struct s_ray
{
	int			x;
	int			y;
	double		camerax;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
	double		wallx;
	int			texx;
	double		step;
	double		texpos;
	int			texy;
	int			color;
}				t_ray;

typedef struct s_sprite
{
	double		x;
	double		y;
	int			texture;
}				t_sprite;

typedef struct s_doors
{
	int			x;
	int			y;
	int			state;
	double		open_amount;
}				t_doors;

typedef struct s_sprite_cast
{
	double		spr_x;
	double		spr_y;
	double		invdet;
	double		trans_x;
	double		trans_y;
	int			screen_x;
	int			dim;
	int			start_y;
	int			end_y;
	int			start_x;
	int			end_x;
}				t_sprite_cast;

typedef struct s_raycast
{
	int			x;
	int			y;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	int			tex_x;
	double		step;
	double		tex_pos;
	int			is_door;
	int			door_idx;
	double		hit_pos;
	int			sky_offset_x;
}				t_raycast;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		screen;
	char		*n_path;
	char		*s_path;
	char		*w_path;
	char		*e_path;
	char		*sprite_path;
	t_img		tex_n;
	t_img		tex_s;
	t_img		tex_w;
	t_img		tex_e;
	t_img		tex_sprite;
	t_img		tex_d;
	int			ground_color;
	int			ceiling_color;
	char		**map;
	t_doors		*doors;
	int			nb_doors;
	int			cam_x;
	int			cam_y;
	char		*map_path;
	int			map_width;
	int			map_height;
	int			direction_player;
	int			fd;
	char		*trim;
	double		z_buffer[1920];
	t_player	player;
	t_img		sky_img;
	t_sprite	sprite;
	int			**heatmap;
	ma_engine	audio_engine;
	ma_sound	monster_sound;
	ma_sound	jumpscare_sound;
	int			has_audio;
}				t_game;

int				init_mlx(t_game *game);
void			init_game(t_game *game);
int				color_recovery(t_game *game, char *line);
void			parsing(char *av[], t_game *game);
void			clean_sprites(t_game *game);
void			clean_exit(t_game *game, t_error error_name);
void			free_tab(char **tab, int limit);
void			my_mlx_pixel_put(t_game *game, int x, int y, int color);
int				raycasting(t_game *game);
int				init_images(t_game *game);
void			valid_map(t_game *game);
void			init_player_cam(t_game *game);
void			calc_line(t_game *game, t_ray *r);
void			draw_column(t_game *game, t_ray *r);

// BONUS :

void			mouse_hook(t_game *game);
void			update_sprite(t_game *game);
void			render_sprite(t_game *game);
int				get_tex_color(t_img *img, int x, int y);
void			render_torch(t_game *game);
void			free_tab_int(int **tab, int limit);
void			bfs(t_game *game);
void			get_next_step(t_game *game, int mx, int my, int *t_xy);
void			init_audio(t_game *game);
void			heatmap(t_game *game);
void			doors(t_game *game);
int				door_idx(t_game *game, int x, int y);
void			interact_door(t_game *game);
int				is_walkable(t_game *game, double x, double y);
void			update_doors_animation(t_game *game);
void			my_mlx_pixel_put(t_game *game, int x, int y, int color);
void			minimap(t_game *game);
void			jumpscare(t_game *game);
void			calc_projection(t_game *game, t_raycast *r);
void			draw_vertical_line(t_game *game, t_raycast *r);

#endif