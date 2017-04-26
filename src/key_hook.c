/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 20:31:41 by upopee            #+#    #+#             */
/*   Updated: 2017/04/27 00:58:58 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "env_utils.h"
#include "key_hook.h"
#include "world_utils.h"
#include "draw_utils.h"

static void		scale_map(int key, t_env *env)
{
	if (key == KEY_PLUS)
		env->cam->view_angle *= 0.9;
	else
		env->cam->view_angle *= 1.1;
}

static void		translate_map(int key, t_env *env)
{
	if (key == KEY_UP)
		env->world->mod.translate.z += 1.0;
	else if (key == KEY_DOWN)
		env->world->mod.translate.z -= 1.0;
	else if (key == KEY_LEFT)
		env->world->mod.translate.x += 1.0;
	else
		env->world->mod.translate.x -= 1.0;
}

static void		rotate_map(int key, t_env *env)
{
	if (key == KEY_X)
		env->world->mod.rot_axis = ft_to_vec3(1.0, 0.0, 0.0);
	else if (key == KEY_Y)
		env->world->mod.rot_axis = ft_to_vec3(0.0, 1.0, 0.0);
	else if (key == KEY_Z)
		env->world->mod.rot_axis = ft_to_vec3(0.0, 0.0, 1.0);
	else if (key == KEY_ALT_LEFT)
		env->world->mod.rot_angle += 1.0;
	else
		env->world->mod.rot_angle -= 1.0;
}

int				key_hook(int key, t_env *env)
{
	if (key == KEY_ESC || key == KEY_Q)
		end_session(env, NULL, EXIT_SUCCESS);
	else if (key == KEY_R)
		reset_modifiers(env->world);
	else if (key == KEY_CTRL)
		print_camera(*(env->cam));
	else if (key == KEY_PLUS || key == KEY_MINUS)
		scale_map(key, env);
	else if (key == KEY_UP || key == KEY_DOWN
				|| key == KEY_LEFT || key == KEY_RIGHT)
		translate_map(key, env);
	else if (key == KEY_X || key == KEY_Y || key == KEY_Z
			|| key == KEY_ALT_RIGHT || key == KEY_ALT_LEFT)
		rotate_map(key, env);
	refresh_window(env);
	return (0);
}
