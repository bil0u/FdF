/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 02:56:03 by upopee            #+#    #+#             */
/*   Updated: 2017/04/14 19:08:09 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_ENV_H
# define MLX_ENV_H

void		end_session(t_scene *world, t_env *env, char *msg, int status);
t_env		*init_env(t_scene *world);

#endif
