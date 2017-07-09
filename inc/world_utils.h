/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 06:37:26 by upopee            #+#    #+#             */
/*   Updated: 2017/07/09 23:34:02 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_UTILS_H
# define WORLD_UTILS_H

void		get_alt_range(t_scene *world);
float		alt_reducer(float alt_range);
void		center_scene(t_scene *world);
void		get_cam_pos(t_scene *world);

#endif
