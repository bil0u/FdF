/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 02:56:03 by upopee            #+#    #+#             */
/*   Updated: 2017/04/05 02:57:15 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_ENV_H
# define MLX_ENV_H

void		end_session(t_map *m, t_mlxenv *e, char *msg, int status);
t_mlxenv	*init_mlxenv(t_map *m);

#endif
