/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 02:03:56 by upopee            #+#    #+#             */
/*   Updated: 2017/04/26 11:04:53 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

void		apply_mat4_to_scene(t_matrix4 *m, t_scene *world,
										t_vector3 (*mat4_mul)());
void		print_scene_values(char *name, t_scene *world);
void		test(t_env *env);

#endif
