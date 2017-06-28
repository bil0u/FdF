/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 08:43:16 by upopee            #+#    #+#             */
/*   Updated: 2017/06/28 00:45:33 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_SET_H
# define COLOR_SET_H

# include "fdf.h"

void	apply_simple_color(t_scene *world, int color);
void	apply_color_set(t_scene *world, t_colors set);
void	set_colors(t_colors *sets);

#endif
