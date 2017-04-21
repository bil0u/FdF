/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 21:02:39 by upopee            #+#    #+#             */
/*   Updated: 2017/04/21 06:26:13 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
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
	while (i < world->height)
	{
		j = 0;
		while (j < world->width)
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

void	test(t_env *env)
{
	t_vector3 scale = {10.0, 10.0, 10.0};
	t_matrix4 m_scale = ft_gen_scale_mat4(scale.x, scale.y, scale.z);

	t_vector3 rot_axis = {1.0, 0.0, 0.0};
	t_matrix4 m_rot = ft_gen_rotation_mat4(0.0, rot_axis.x, rot_axis.y, rot_axis.z);

	t_vector3 translation = {0.0, 0.0, 0.0};
	t_matrix4 m_trans = ft_gen_translate_mat4(translation.x, translation.y, translation.z);

	t_matrix4 m_model = ft_mat4_mul_mat4(&m_scale, &m_rot);
	m_model = ft_mat4_mul_mat4(&m_model, &m_trans);

	t_vector3 eye = {(0.0), (2.0), (6.0)};
	t_vector3 center = {0.0, 0.0, 0.0};
	t_vector3 up = {0.0, 0.0, 1.0};
	//float mid_x = (float)env->world->width * 0.5;
	//float mid_y = (float)env->world->height * 0.5;
	//float half_dist = sqrtf(mid_x * mid_x + mid_y * mid_y);
	//env->cam->far = half_dist * 2.0;
	t_matrix4 m_view = ft_lookat(env->cam, &eye, &center, &up);

	t_matrix4 m_proj = ft_perspective_proj_mat4(env->cam->view_angle, env->cam->near, env->cam->far);

	t_matrix4 m_all = ft_mat4_mul_mat4(&m_model, &m_view);
	m_all = ft_mat4_mul_mat4(&m_all, &m_proj);
	printf("-- WORLD TRANSFORMS --\n");
	print_mat4(&m_scale, "Scale");
	print_mat4(&m_rot, "Rotation");
	print_mat4(&m_trans, "Translation");
	printf("-- MVP MATRICES --\n");
	print_mat4(&m_model, "Model Matrix");
	print_mat4(&m_view, "View Matrix");
	print_mat4(&m_proj, "Projection Matrix");
	print_mat4(&m_all, "> Final Matrix <");
	printf("------------------\n");
	print_scene_values(">>> BEFORE TRANSFORMATION <<<", env->world);
//	apply_mat4_to_scene(&m_model, env->world, &ft_mat4_mul_quat);
//	print_scene_values(">>> MODEL <<<", env->world);
//	apply_mat4_to_scene(&m_view, env->world, &ft_mat4_mul_quat);
//	print_scene_values(">>> VIEW <<<", env->world);
//	apply_mat4_to_scene(&m_proj, env->world, &ft_mat4_mul_quat);

	apply_mat4_to_scene(&m_all, env->world, &ft_mat4_mulnorm_quat);

	print_scene_values(">>> AFTER TRANSFORMATION <<<", env->world);
	print_cam(env->cam);
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
	env = init_env(world);

	test(env);

	mlx_key_hook(env->m_win->id, &key_hook, env);
	mlx_expose_hook(env->m_win->id, &refresh_window, env);
	mlx_loop(env->m_env->init_id);
	end_session(env, NULL, EXIT_SUCCESS);
	return (0);
}
