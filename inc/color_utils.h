/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 08:43:16 by upopee            #+#    #+#             */
/*   Updated: 2017/07/26 20:20:21 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_UTILS_H
# define COLOR_UTILS_H

# include "fdf.h"

void	apply_markedset(t_scene *world, t_colors set);
void	apply_colorset(t_scene *world, t_colors set);
void	apply_color(t_scene *world, int color);
void	init_colors(t_colors *sets);

#endif
