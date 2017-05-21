/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 22:08:57 by upopee            #+#    #+#             */
/*   Updated: 2017/05/20 00:12:09 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "env_utils.h"

static t_matrix4	get_model_matrix(t_mod mod)
{
	t_matrix4	scale;
	t_matrix4	rotate;
	t_matrix4	translate;
	t_matrix4	model;

	scale = ft_gen_scale_mat4(mod.scale);
	rotate = ft_gen_euler_rotation_mat4(mod.rot_x, mod.rot_y, mod.rot_z);
	translate = ft_gen_translate_mat4(mod.translate);
	model = ft_mat4_mul_mat4(rotate, scale);
	model = ft_mat4_mul_mat4(translate, model);
	return (model);
}

static t_matrix4	get_mvp_matrix(t_camera *cam, t_mod mod)
{
	t_matrix4	model;
	t_matrix4	view;
	t_matrix4	projection;
	t_matrix4	mvp;

	model = get_model_matrix(mod);
	view = ft_lookat(cam, mod.cam_eye, mod.cam_to, mod.cam_upv);
	if (mod.proj_type == PERSPECTIVE_PROJ)
		projection = ft_persproj_mat4(cam->view_angle * mod.zoom,
										cam->near, cam->far, cam->aspect_ratio);
	else //if (mod.proj_type == ORTHOGRAPHIC_PROJ)
	projection = ft_orthoproj_mat4(cam->view_angle * mod.zoom,
										cam->near, cam->far, cam->aspect_ratio);
	mvp = ft_mat4_mul_mat4(view, model);
	mvp = ft_mat4_mul_mat4(projection, mvp);
	return (mvp);
}

static t_vertex2i	v_proj(t_vector3 vec, t_matrix4 mat, int img_w, int img_h)
{
	t_quater	hom;
	t_vector3	ndc;
	t_vertex2i	proj;

	hom = ft_vec3_to_quat(vec, 1.0);
	hom = ft_mat4_postmul_quat(hom, mat);
	ndc = ft_quat_to_vec3(hom);
	proj = ft_viewport_tlc(ndc, ft_to_ver2i(0, 0), img_w, img_h);
	return(proj);
}

static int		is_visible(t_vertex2i pt, int width, int heigt)
{
	return (pt.x >= 0 && pt.x < width
			&& pt.y >= 0 && pt.y < heigt);
}

static void		draw_map(t_env *env, t_scene *world, t_mlximg *img)
{
	t_matrix4		final;
	t_line			h;
	t_line			v;
	int				i;
	int				j;

	final = get_mvp_matrix(env->cam, world->mod);
	i = world->height;
	while (i--)
	{
		j = world->width;
		h.b = v_proj(world->map[i][j], final, img->width, img->height);
		while (j-- > 1)
		{
			h.a = h.b;
			h.b = v_proj(world->map[i][j - 1], final, img->width, img->height);
			mlx_bresenham(img, h.a, h.b);
		}
		if (is_visible(h.b, img->width, img->height))
			pixel_to_img(img, h.b.x, h.b.y, 0x00FFFFFF);
	}
}

int				refresh_window(t_env *env)
{
	t_mlxenv	*mlx;
	t_mlxwin	*win;
	t_mlximg	*img;

	mlx = env->m_env;
	win = env->m_win;
	if (!(env->m_img = init_mlximg(mlx->init_id, win->width, win->height)))
		end_session(env, "mlx: cannot create image", EXIT_FAILURE);
	img = env->m_img;
	draw_map(env, env->world, img);
	mlx_put_image_to_window(mlx->init_id, win->id, img->id, 0, 0);
	del_mlximg(mlx->init_id, img);
	return (0);
}
