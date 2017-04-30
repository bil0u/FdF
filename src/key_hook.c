/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 20:31:41 by upopee            #+#    #+#             */
/*   Updated: 2017/04/30 18:53:48 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "env_utils.h"
#include "key_hook.h"
#include "world_utils.h"
#include "draw_utils.h"

static void		scale_map(int key, t_mod *mod)
{
	if (key == KEY_PLUS)
		mod->scale.y += 0.05;
	else
		mod->scale.y -= 0.05;
}

static void		zoom_map(int key, t_mod *mod)
{
	if (key == KEY_PLUS && mod->zoom > MAX_ZOOM)
		mod->zoom *= 0.9;
	else if (mod->zoom < MIN_ZOOM)
		mod->zoom *= 1.1;
}

static void		translate_map(int key, t_mod *mod)
{
	if (key == KEY_UP)
		mod->translate.z -= 2.0;
	else if (key == KEY_DOWN)
		mod->translate.z += 2.0;
	else if (key == KEY_LEFT)
		mod->translate.x -= 2.0;
	else
		mod->translate.x += 2.0;
}

static void		rotate_map(int key, t_mod *mod)
{
	if (key == KEY_LEFT)
		mod->rot_angle += 1.0;
	else if (key == KEY_RIGHT)
		mod->rot_angle -= 1.0;
}

int				key_hook(int key, t_env *env)
{
	t_mod	*mod;

	mod = &(env->world->mod);
	if (key == KEY_ESC || key == KEY_Q)
		end_session(env, NULL, EXIT_SUCCESS);
	else if (key == KEY_DEL)
		reset_modifiers(env->world);
	else if (key == KEY_R)
		mod->rot_bool = TRUE;
	else if (key == KEY_T)
		mod->rot_bool = FALSE;
	else if (key == KEY_Z)
		mod->zoom_bool = TRUE;
	else if (key == KEY_A)
		mod->zoom_bool = FALSE;
	else if (key == KEY_PLUS || key == KEY_MINUS)
		mod->zoom_bool == TRUE ? zoom_map(key, mod) : scale_map(key, mod);
	else if (key == KEY_UP || key == KEY_DOWN
			|| key == KEY_LEFT || key == KEY_RIGHT)
		mod->rot_bool == TRUE ? rotate_map(key, mod) : translate_map(key, mod);
	refresh_window(env);
	return (0);
}
