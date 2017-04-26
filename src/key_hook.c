/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 20:31:41 by upopee            #+#    #+#             */
/*   Updated: 2017/04/26 09:53:28 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "env_utils.h"
#include "key_hook.h"
#include "world_utils.h"
#include "draw_utils.h"

int		key_hook(int keycode, t_env *env)
{
	if (keycode == KEY_ESC)
		end_session(env, NULL, EXIT_SUCCESS);
	else if (keycode == KEY_R)
		reset_modifiers(env->world);
	else if (keycode == KEY_CTRL)
		print_camera(*(env->cam));
	refresh_window(env);
	return (0);
}
