/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 09:49:08 by upopee            #+#    #+#             */
/*   Updated: 2017/07/05 20:47:07 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "libgraphic.h"
# include "rgb_colors.h"
# include <time.h>

# define MAP_SEPARATOR ' '

# define FPS_BUFF_SIZE 60
# define FPS_REFRESH_TIME 1.0

# define STR_BUFF_SIZE 8
# define STR_COLOR 0xFFFFFF

# define NB_PROJS 2
# define ORTHOGRAPHIC_PROJ 0
# define PERSPECTIVE_PROJ 1

# define NB_COLORSETS 4
# define MAX_COLORS 256

# define DEFAULT_SCALE_X 1.0
# define DEFAULT_SCALE_Y 0.8
# define DEFAULT_SCALE_Z 1.0
# define REDUCE_LIMIT 50.0

# define DEFAULT_ROT_X 0.0
# define DEFAULT_ROT_Y -15.0
# define DEFAULT_ROT_Z 0.0
# define R_SPEED 1.5

# define DEFAULT_ZOOM 1.0
# define MAX_ZOOM 0.1
# define MIN_ZOOM 2.3
# define Z_PSPEED 0.8
# define Z_MSPEED 1.2

# define T_SPEED 2.0

# define REDUCE_FACTOR 0.5
# define ALT_FACTOR 0.05

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define EXPOSE 12
# define KEY_PRESS_MASK (1L << 0)
# define KEY_RELEASE_MASK (1L << 1)
# define EXPOSE_MASK (1L << 15)

typedef int		t_colorset[MAX_COLORS];

typedef struct	s_colors
{
	int			curr_set;
	t_colorset	colors[NB_COLORSETS];
	int			nb_colors[NB_COLORSETS];
	int			curr_color[NB_COLORSETS];
	float		marked_alt[NB_COLORSETS];
	int			marked_colorup[NB_COLORSETS];
}				t_colors;


typedef	struct	s_mod
{
	t_colors	col;
	t_vector3	cam_eye;
	t_vector3	cam_to;
	t_vector3	cam_upv;
	t_vector3	translate;
	t_vector3	scale;
	float		rot_x;
	float		rot_y;
	float		rot_z;
	float		zoom;
	int			proj_type;
	int			keymod;
}				t_mod;

# define QUIT (1)
# define RESET (1 << 1)
# define ROTATE (1 << 2)
# define ZOOM (1 << 3)
# define PTS_ONLY (1 << 4)
# define NEXT_PROJ (1 << 5)
# define NEXT_COLOR (1 << 6)
# define MARKED_UP (1 << 7)
# define MARKED_LOW (1 << 8)
# define FULL_SET (1 << 9)
# define PLUS (1 << 10)
# define MINUS (1 << 11)
# define UP (1 << 12)
# define DOWN (1 << 13)
# define LEFT (1 << 14)
# define RIGHT (1 << 15)
# define DEBUG (1 << 16)
# define HELP (1 << 17)

# define QUIT_SET(x) (x & 1)
# define RESET_SET(x) ((x >> 1) & 1)
# define ROTATE_SET(x) ((x >> 2) & 1)
# define ZOOM_SET(x) ((x >> 3) & 1)
# define PTS_ONLY_SET(x) ((x >> 4) & 1)
# define NEXT_PROJ_SET(x) ((x >> 5) & 1)
# define NEXT_COLOR_SET(x) ((x >> 6) & 1)
# define MARKED_UP_SET(x) ((x >> 7) & 1)
# define MARKED_LOW_SET(x) ((x >> 8) & 1)
# define FULL_SET_SET(x) ((x >> 9) & 1)
# define PLUS_SET(x) ((x >> 10) & 1)
# define MINUS_SET(x) ((x >> 11) & 1)
# define UP_SET(x) ((x >> 12) & 1)
# define DOWN_SET(x) ((x >> 13) & 1)
# define LEFT_SET(x) ((x >> 14) & 1)
# define RIGHT_SET(x) ((x >> 15) & 1)
# define DEBUG_SET(x) ((x >> 16) & 1)
# define HELP_SET(x) ((x >> 17) & 1)

# define OFF(x) (~(x))

typedef	struct	s_scene
{
	t_vertex3f	**map;
	int			width;
	int			height;
	float		alt_range;
	float		alt_min;
	float		alt_max;
	t_matrix4	center_matrix;
	t_mod	mod;
}				t_scene;

typedef struct	s_env
{
	t_mlxenv	*m_env;
	t_mlxwin	*m_win;
	t_mlxfbuf	*m_fbuf;
	t_scene		*world;
	t_camera	*cam;
	float		last_time;
	int			nb_frames;
	char		sbuff[STR_BUFF_SIZE];
}				t_env;

typedef struct	s_line
{
	t_vertex2i	a;
	t_vertex2i	b;
	int			long_len;
	int			increment;
	float		step;
}				t_line;

#endif
