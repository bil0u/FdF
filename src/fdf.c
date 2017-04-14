/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 21:02:39 by upopee            #+#    #+#             */
/*   Updated: 2017/04/14 20:02:48 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx_env.h"
#include "parse_input.h"
#include "matrix_utils.h"

#ifdef DEBUG

#include <stdio.h>

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
			print_vec4(&(world->map[i][j]));
		printf("  ");
			j++;
		}
		printf("\n");
		i++;
	}
	printf("---------------------\n");
}

void	matrix_test(t_scene *world)
{
	t_matrix4	m_local;
	t_matrix4	m_trans;
	t_matrix4	m_scale;
	t_matrix4	m_rot;

	m_trans = ft_gen_translate_mat4(0.0, 0.0, 0.0);
	print_mat4(&m_trans, "Translation");
	m_scale = ft_gen_scale_mat4(1.0, 1.0, 1.0);
	print_mat4(&m_scale, "Scale");
	m_rot = ft_gen_rotation_mat4(0.0, 0.0, 0.0, 0.0);
	print_mat4(&m_rot, "Rotation");
	m_local = ft_mat4_mul_mat4(&m_scale, &m_rot);
	m_local = ft_mat4_mul_mat4(&m_local, &m_trans);
	print_mat4(&m_local, "Final");
	print_scene_values("> Before <", world);
	apply_mat4_to_scene(&m_local, world);
	print_scene_values("> After <", world);
}
#endif

int		main(int argc, char **argv)
{
	t_env		*env;
	t_scene		*world;

	if (argc != 2)
		end_session(NULL, NULL, "usage : ./fdf [path/to/file]", EXIT_FAILURE);
	world = input_to_scene(argv[1]);
	center_scene(world);
	matrix_test(world);
	env = init_env(world);
//	mlx_loop(env->m_env->init_id);
	end_session(world, env, NULL, EXIT_SUCCESS);
	return (0);
}
