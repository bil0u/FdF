/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 22:08:57 by upopee            #+#    #+#             */
/*   Updated: 2017/06/28 02:33:03 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "draw_utils.h"
#include "env_utils.h"

static t_matrix4	get_model_matrix(t_mod mod, t_matrix4 center_matrix)
{
	t_matrix4	scale;
	t_matrix4	rotate;
	t_matrix4	translate;
	t_matrix4	model;

	scale = ft_gen_scale_mat4(mod.scale);
	rotate = ft_gen_euler_rotation_mat4(mod.rot_x, mod.rot_y, mod.rot_z);
	translate = ft_gen_translate_mat4(mod.translate);
	model = ft_mat4_mul_mat4(scale, center_matrix);
	model = ft_mat4_mul_mat4(rotate, model);
	model = ft_mat4_mul_mat4(translate, model);
	return (model);
}

static t_matrix4	get_mvp_matrix(t_camera *cam, t_scene *w)
{
	t_matrix4	model;
	t_matrix4	view;
	t_matrix4	projection;
	t_matrix4	mvp;

	model = get_model_matrix(w->mod, w->center_matrix);
	view = ft_lookat(cam, w->mod.cam_eye, w->mod.cam_to, w->mod.cam_upv);
	if (w->mod.proj_type == PERSPECTIVE_PROJ)
		projection = ft_persproj_mat4(cam->view_angle * w->mod.zoom,
										cam->near, cam->far, cam->aspect_ratio);
	else
		projection = ft_orthoproj_mat4(cam->view_angle * w->mod.zoom,
										cam->near, cam->far, cam->aspect_ratio);
	mvp = ft_mat4_mul_mat4(view, model);
	mvp = ft_mat4_mul_mat4(projection, mvp);
	return (mvp);
}


int				refresh_window(t_env *env)
{
	t_matrix4		final;

	if (!(env->m_img = init_mlximg(env->m_env->init_id,
									env->m_win->width, env->m_win->height)))
		end_session(env, "mlx: cannot create image", EXIT_FAILURE);
	final = get_mvp_matrix(env->cam, env->world);
	if (env->world->mod.points_only == FALSE)
	{
		draw_lines(env->world, env->m_img, final);
		draw_columns(env->world, env->m_img, final);
	}
	else
		draw_points(env->world, env->m_img, final);
	mlx_put_image_to_window(env->m_env->init_id,
								env->m_win->id, env->m_img->id, 0, 0);
	del_mlximg(env->m_env->init_id, env->m_img);
	return (0);
}
