/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 09:49:08 by upopee            #+#    #+#             */
/*   Updated: 2017/04/14 19:32:10 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define MAP_SEPARATOR ' '

# include "libft.h"
# include "libgraphic.h"

typedef	struct	s_scene
{
	t_vector4	**map;
	int			nb_rows;
	int			nb_columns;
}				t_scene;

typedef struct	s_env
{
	t_mlxenv	*m_env;
	t_mlxwin	*m_win;
	t_mlximg	*m_img;
	t_scene		*world;
}				t_env;

#endif
