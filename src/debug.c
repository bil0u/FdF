/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 02:01:39 by upopee            #+#    #+#             */
/*   Updated: 2017/04/26 10:57:03 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef DEBUG

#include <math.h>
#include <stdio.h>
#include "fdf.h"
#include "libgraphic.h"

void			apply_mat4_to_scene(t_matrix4 m, t_scene *world,
										t_vector3 (*mat4_mul)())
{
	int			i;
	int			j;

	i = world->height;
	while (i--)
	{
		j = world->width;
		while (j--)
			world->map[i][j] = (*mat4_mul)(m, world->map[i][j]);
	}
}

void	print_scene_values(char *name, t_scene *world)
{
	int 		i;
	int 		j;
	i = 0;
	printf("%-15s\n", name);
	while (i < world->height)
	{
		j = 0;
		while (j < world->width)
		{
			print_vec3(world->map[i][j]);
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
	t_matrix4 m_scale;
	t_matrix4 m_rot;
	t_matrix4 m_trans;
	t_matrix4 m_model;

	m_scale = ft_gen_scale_mat4(env->world->mod.scale);
	m_rot = ft_gen_rotation_mat4(env->world->mod.rot_angle, env->world->mod.rot_axis);
	m_trans = ft_gen_translate_mat4(env->world->mod.translate);

	m_model = ft_mat4_mul_mat4(m_scale, m_rot);
	m_model = ft_mat4_mul_mat4(m_model, m_trans);

	t_vector3 eye = {(0.0), (0.0), (15.0)};
	t_vector3 center = {0.0, 0.0, 0.0};
	t_vector3 up = {0.0, 1.0, 0.0};
	t_matrix4 m_view = ft_lookat(env->cam, eye, center, up);
	t_matrix4 m_proj = ft_persproj_mat4(env->cam->view_angle, env->cam->near, env->cam->far, env->cam->aspect_ratio);
	t_matrix4 m_all = ft_mat4_mul_mat4(m_view, m_model);
	m_all = ft_mat4_mul_mat4(m_proj, m_all);

	if (1)
	{
		printf("-- WORLD TRANSFORMS --\n");
		print_mat4(m_scale, "Scale");
		print_mat4(m_rot, "Rotation");
		print_mat4(m_trans, "Translation");
		printf("-- MVP MATRICES --\n");
		print_scene_values("[START] >> Initial values <<", env->world);
		printf("--\n");
		apply_mat4_to_scene(m_model, env->world, &ft_mat4_premul_vec3);
		print_mat4(m_model, "Model Matrix - Scale Rot & Transl.");
		print_scene_values("[MODEL = WORLD] > World Values :", env->world);
		printf("--\n");
		apply_mat4_to_scene(m_view, env->world, &ft_mat4_premul_vec3);
		print_mat4(m_view, "View Matrix");
		print_scene_values("[WORLD -> EYE] > Camera values :", env->world);
		printf("--\n");
		apply_mat4_to_scene(m_proj, env->world, &ft_mat4_premul_vec3);
		print_mat4(m_proj, "Projection Matrix");
		print_scene_values("[EYE -> PROJECTION] > Clip values :", env->world);
		printf("--\n");
		print_scene_values(">>> AFTER TRANSFORMATION <<<", env->world);
		printf("--\n");
		print_camera(*(env->cam));
	}
	else
	{
		print_scene_values("[START] >> Initial values <<", env->world);
		apply_mat4_to_scene(m_all, env->world, &ft_mat4_premul_vec3);
		print_scene_values(">>> AFTER TRANSFORMATION <<<", env->world);
	}

}
#endif
