/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:57:55 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/20 17:07:01 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char		*map_path;
	int			map_width;
	int			map_height;
	int			direction_player;
	int			fd;
	char		*trim;
	t_player	player;
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
void			data_counter_init(int data_counter[]);
char			*skip(char *line);
void			data_recovery(t_game *game, char *line, int data_counter[]);
int				search_longest(t_game *game);
int				nbr_line(t_game *game, char *first_line);
void			filler(t_game *game, size_t end_line, char *line, int line_nbr);
int				ft_strisdigits(char *str);
int				pass_line(int fd, char *line);
void			rotate_player_key(t_game *game, double rot);
void			move_lr(t_game *game, double speed);
void			move_fb(t_game *game, double speed);
int				get_tex_color(t_img *img, int x, int y);
void			process_trim(t_game *game, int c[6]);

#endif