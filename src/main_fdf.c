/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 21:02:39 by upopee            #+#    #+#             */
/*   Updated: 2017/07/16 01:03:05 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "parse_input.h"
#include "hook_mlx.h"
#include "env_utils.h"
#include "window_utils.h"
#include <math.h>

int		main(int argc, char **argv)
{
	t_env		*env;
	t_scene		*wld;
	void		*eid;
	void		*wid;

	if (argc != 2)
		end_session(NULL, "usage : ./fdf [path/to/file]", EXIT_FAILURE);
	wld = input_to_scene(argv[1]);
	env = init_env(wld);
	eid = env->m_env->init_id;
	wid = env->m_win->id;
	mlx_loop_hook(eid, &loop_hook, env);
	mlx_hook(wid, KEY_PRESS, KEY_PRESS_MASK, &key_press, &(wld->mod.keymod));
	mlx_hook(wid, KEY_RELEASE, KEY_RELEASE_MASK,
			&key_release, &(wld->mod.keymod));
	mlx_hook(wid, EXPOSE, EXPOSE_MASK, &refresh_window, env);
	env->last_time = clock() / CLOCKS_PER_SEC;
	mlx_loop(eid);
	return (0);
}
