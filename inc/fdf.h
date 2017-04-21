/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 09:49:08 by upopee            #+#    #+#             */
/*   Updated: 2017/04/21 04:46:50 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define MAP_SEPARATOR ' '

# define X_SCALE 1
# define Y_SCALE 1
# define Z_SCALE 1

# include "libft.h"
# include "libgraphic.h"

typedef	struct	s_scene
{
	t_quater	**map;
	t_quater	center;
	int			nb_rows;
	int			nb_columns;
}				t_scene;

typedef struct	s_env
{
	t_mlxenv	*m_env;
	t_mlxwin	*m_win;
	t_mlximg	*m_img;
	t_scene		*world;
	t_camera	*cam;
}				t_env;

#endif
