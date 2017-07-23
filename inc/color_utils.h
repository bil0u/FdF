/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 08:43:16 by upopee            #+#    #+#             */
/*   Updated: 2017/07/19 15:08:49 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_SET_H
# define COLOR_SET_H

# include "fdf.h"

void	apply_markedset(t_scene *world, t_colors set);
void	apply_colorset(t_scene *world, t_colors set);
void	apply_color(t_scene *world, int color);
void	init_colors(t_colors *sets);

#endif
