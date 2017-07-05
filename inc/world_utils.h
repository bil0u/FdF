/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 06:37:26 by upopee            #+#    #+#             */
/*   Updated: 2017/07/05 03:08:08 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_UTILS_H
# define WORLD_UTILS_H

void	center_scene(t_scene *world);
void	get_cam_pos(t_scene *world);
void	reset_modifiers(t_scene *world, t_keymod *km);

#endif
