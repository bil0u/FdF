/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 09:49:08 by upopee            #+#    #+#             */
/*   Updated: 2017/05/19 22:53:06 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "libgraphic.h"

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

typedef	struct	s_mod
{
	int			rot_bool;
	int			zoom_bool;
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
	t_vector3	**map;;
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
}				t_line;

#endif
