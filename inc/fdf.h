/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 09:49:08 by upopee            #+#    #+#             */
/*   Updated: 2017/07/01 18:29:59 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "libgraphic.h"
# include "rgb_colors.h"

# define MAP_SEPARATOR ' '

# define FPS_MAX 60

# define NB_PROJS 2
# define ORTHOGRAPHIC_PROJ 0
# define PERSPECTIVE_PROJ 1

# define NB_COLORSETS 2
# define MAX_COLORS 15

# define DEFAULT_SCALE_X 1.0
# define DEFAULT_SCALE_Y 0.1
# define DEFAULT_SCALE_Z 1.0
# define REDUCE_LIMIT 50.0

# define DEFAULT_ROT_X 0.0
# define DEFAULT_ROT_Y -15.0
# define DEFAULT_ROT_Z 0.0
# define R_SPEED 1.5

# define DEFAULT_ZOOM 1.0
# define MAX_ZOOM 0.01
# define MIN_ZOOM 2.3
# define Z_PSPEED 0.8
# define Z_MSPEED 1.2

# define T_SPEED 2.0

# define REDUCE_FACTOR 0.5
# define ALT_FACTOR 0.05

# define KEY_PRESS 2
# define KEY_PRESS_MASK (1L << 0)
# define KEY_RELEASE 3
# define KEY_RELEASE_MASK (1L << 1)

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


typedef	struct	s_wldmod
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
}				t_wldmod;

typedef struct	s_keymod
{
	int			quit : 1;
	int			reset : 1;
	int			rotate : 1;
	int			zoom : 1;
	int			pts_only : 1;
	int			next_proj : 1;
	int			next_color : 1;
	int			up_marked_alt : 1;
	int			low_marked_alt : 1;
	int			full_colorset : 1;
	int			plus : 1;
	int			minus : 1;
	int			up : 1;
	int			down : 1;
	int			left : 1;
	int			right : 1;
}				t_keymod;

typedef	struct	s_scene
{
	t_vertex3f	**map;
	int			width;
	int			height;
	float		alt_range;
	float		alt_min;
	float		alt_max;
	t_matrix4	center_matrix;
	t_wldmod	mod;
}				t_scene;

typedef struct	s_env
{
	t_mlxenv	*m_env;
	t_mlxwin	*m_win;
	t_mlxfbuf	*m_fbuf;
	t_scene		*world;
	t_camera	*cam;
	t_keymod	keymod;
	int			debug;
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
