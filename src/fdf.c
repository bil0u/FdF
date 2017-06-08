/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 21:02:39 by upopee            #+#    #+#             */
/*   Updated: 2017/06/05 04:53:25 by upopee           ###   ########.fr       */
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
	mlx_do_key_autorepeaton(env->m_win->id);
	mlx_hook(env->m_win->id, KEY_PRESS, KEY_PRESS_MASK, &key_hook, env);
	mlx_expose_hook(env->m_win->id, &refresh_window, env);
	mlx_loop(env->m_env->init_id);
	end_session(env, NULL, EXIT_SUCCESS);
	return (0);
}
