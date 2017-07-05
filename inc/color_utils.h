/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 08:43:16 by upopee            #+#    #+#             */
/*   Updated: 2017/07/05 17:40:27 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_SET_H
# define COLOR_SET_H

# include "fdf.h"

void	apply_simple_color(t_scene *world, int color);
void	apply_color_set(t_scene *world, t_colors set);
void	init_colorsets(t_colors *sets);

#endif
