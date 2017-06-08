/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 09:49:08 by upopee            #+#    #+#             */
/*   Updated: 2017/06/07 03:01:08 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "libgraphic.h"
# include "rgb_colors.h"

# define MAP_SEPARATOR ' '

# define DEFAULT_SCALE_X 1.0
# define DEFAULT_SCALE_Y 1.0
# define DEFAULT_SCALE_Z 1.0
# define DEFAULT_ROT_X 0.0
# define DEFAULT_ROT_Y -15.0
# define DEFAULT_ROT_Z 0.0
# define DEFAULT_ZOOM 1.0
# define MAX_ZOOM 0.01
# define MIN_ZOOM 2.3
# define REDUCE_LIMIT 50.0
# define REDUCE_FACTOR 0.03

# define KEY_PRESS 2
# define KEY_PRESS_MASK (1L << 0)

# define ORTHOGRAPHIC_PROJ 1
# define PERSPECTIVE_PROJ 2

# define NB_COLORSETS 2
# define MAX_COLORS 8

typedef int		t_colorset[MAX_COLORS];

typedef struct	s_colors
{
	int			full_set;
	int			curr_set;
	int			curr_color;
	t_colorset	colors[NB_COLORSETS];
	int			nb_colors[NB_COLORSETS];
	float		marked_alt[NB_COLORSETS];
	int			marked_color[NB_COLORSETS];
	float		slice_up;
	float		slice_down;
}				t_colors;


typedef	struct	s_mod
{
	int			rot_bool;
	int			zoom_bool;
	int			points_only;
	t_colors	col;
	int			proj_type;
	t_vector3	cam_eye;
	t_vector3	cam_to;
	t_vector3	cam_upv;
	t_vector3	translate;
	t_vector3	scale;
	float		rot_x;
	float		rot_y;
	float		rot_z;
	float		zoom;
}				t_mod;

typedef	struct	s_scene
{
	t_vertex3f	**map;
	int			width;
	int			height;
	int			alt_range;
	int			alt_min;
	int			alt_max;
	t_mod		mod;
}				t_scene;

typedef struct	s_env
{
	t_mlxenv	*m_env;
	t_mlxwin	*m_win;
	t_mlximg	*m_img;
	t_scene		*world;
	t_camera	*cam;
	int			debug;
}				t_env;

typedef struct	s_line
{
	t_vertex2i	a;
	t_vertex2i	b;
	int			long_len;
	int			increment;
}				t_line;

#endif
