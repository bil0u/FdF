/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mlx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 20:33:09 by upopee            #+#    #+#             */
/*   Updated: 2017/07/26 20:20:36 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOK_MLX_H
# define HOOK_MLX_H

int		key_press(int keycode, int *keys);
int		key_release(int keycode, int *keys);
int		loop_hook(t_env *env);

#endif
