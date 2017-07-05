/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 21:02:39 by upopee            #+#    #+#             */
/*   Updated: 2017/07/05 02:53:59 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"
#include "parse_input.h"
#include "key_hook.h"
#include "env_utils.h"
#include "refresh_window.h"
#include "debug.h"
#include "world_utils.h"

int		main(int argc, char **argv)
{
	t_env		*env;
	t_scene		*world;

	if (argc != 2)
		end_session(NULL, "usage : ./fdf [path/to/file]", EXIT_FAILURE);
	world = input_to_scene(argv[1]);
	env = init_env(world);
	mlx_do_key_autorepeatoff(env->m_win->id);
	mlx_hook(env->m_win->id, KEY_PRESS, KEY_PRESS_MASK, &key_press, &(env->keymod));
	mlx_hook(env->m_win->id, KEY_RELEASE, KEY_RELEASE_MASK, &key_release, &(env->keymod));
	mlx_hook(env->m_win->id, EXPOSE, EXPOSE_MASK, &refresh_window, env);
	mlx_hook(env->m_win->id, DESTROYNOTIFY, NOEVENT_MASK, &destroy_event, env);
	mlx_loop_hook(env->m_env->init_id, &loop_hook, env);
	mlx_loop(env->m_env->init_id);
	end_session(env, NULL, EXIT_SUCCESS);
	return (0);
}
