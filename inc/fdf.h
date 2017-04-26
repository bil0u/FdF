/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 09:49:08 by upopee            #+#    #+#             */
/*   Updated: 2017/04/26 17:02:49 by upopee           ###   ########.fr       */
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
# define DEFAULT_ROT_ANGLE 0.0
# define DEFAULT_ZOOM 1.0

typedef	struct	s_mod
{
	t_vector3	cam_eye;
	t_vector3	cam_to;
	t_vector3	cam_upv;
	t_vector3	translate;
	t_vector3	scale;
	t_vector3	rot_axis;
	float		rot_angle;
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

#endif
