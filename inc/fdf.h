/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 09:49:08 by upopee            #+#    #+#             */
/*   Updated: 2017/04/04 16:40:45 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define MAP_SEPARATOR ' '

typedef struct	s_map
{
	int			**tab;
	int			nb_lines;
	int			nb_columns;
}				t_map;

typedef struct	s_mlxwin
{
	void		*id;
	int			size_x;
	int			size_y;
}				t_mlxwin;

typedef struct	s_mlximg
{
	void		*id;
	int			size_x;
	int			size_y;
	int			bpp;
	int			size_line;
	int			endian;
}				t_mlximg;

typedef struct	s_env
{
	void		*init_id;
	t_mlxwin	win;
	t_mlximg	img1;
}				t_env;

#endif
