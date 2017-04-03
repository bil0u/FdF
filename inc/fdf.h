/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 09:49:08 by upopee            #+#    #+#             */
/*   Updated: 2017/04/03 22:42:25 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define MAP_SEPARATOR ' '

typedef struct	s_map
{
	int		**tab;
	int		nb_lines;
	int		nb_columns;
}				t_map;

#endif
