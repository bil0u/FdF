/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 21:02:39 by upopee            #+#    #+#             */
/*   Updated: 2017/04/18 05:22:02 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "parse_input.h"
#include "key_hook.h"
#include "env_utils.h"
#include "draw_utils.h"
#include "matrix_utils.h"

#ifdef DEBUG

#include <stdio.h>

void	print_quater(char *name, t_quater *q)
{
	printf("-> %s <-\n", name);
	print_quat(q);
	printf("\n\n");
}

void	print_scene_values(char *name, t_scene *world)
{
	int 		i;
	int 		j;
	i = 0;
	printf("-- %-15s --\n", name);
	while (i < world->nb_rows)
	{
		j = 0;
		while (j < world->nb_columns)
		{
			print_quat(&(world->map[i][j]));
		printf("  ");
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}

void	matrix_test(t_scene *world)
{
	t_matrix4	m_local;
	t_matrix4	m_trans;
	t_matrix4	m_scale;
	t_matrix4	m_rot;
	t_quater	q_test;

	m_scale = ft_gen_scale_mat4(3.0, 3.0, 3.0);
	m_rot = ft_gen_rotation_mat4(0.0, 0.0, 0.0, 0.0);
	m_trans = ft_gen_translate_mat4(0.0, 0.0, 0.0);
	m_local = ft_mat4_mul_mat4(&m_scale, &m_rot);
	m_local = ft_mat4_mul_mat4(&m_local, &m_trans);

	q_test = ft_mat4_to_quat(&m_local);

	print_mat4(&m_scale, "Scale");
	print_mat4(&m_rot, "Rotation");
	print_mat4(&m_trans, "Translation");
	print_mat4(&m_local, "Final");

	print_quater("quater test", &q_test);

	print_scene_values(">>> Before <<<", world);
	apply_mat4_to_scene(&m_local, world);
	print_scene_values(">>> After <<<", world);
}
#endif

int		main(int argc, char **argv)
{
	t_env		*env;
	t_scene		*world;

	if (argc != 2)
		end_session(NULL, "usage : ./fdf [path/to/file]", EXIT_FAILURE);
	world = input_to_scene(argv[1]);
	center_scene(world);
	matrix_test(world);
	env = init_env(world);
	mlx_key_hook(env->m_win->id, &key_hook, env);
	mlx_expose_hook(env->m_win->id, &refresh_window, env);
	mlx_loop(env->m_env->init_id);
	end_session(env, NULL, EXIT_SUCCESS);
	return (0);
}
