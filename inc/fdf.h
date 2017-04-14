/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 09:49:08 by upopee            #+#    #+#             */
/*   Updated: 2017/04/14 04:55:22 by upopee           ###   ########.fr       */
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
#endif
