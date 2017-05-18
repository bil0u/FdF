/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 22:08:57 by upopee            #+#    #+#             */
/*   Updated: 2017/05/04 10:29:21 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "env_utils.h"

static void		pixel_to_img(t_mlximg *img, int x, int y, unsigned int color)
{
	char			*curr_pixel;
	int				i;
	int				j;

	i = img->bpp / 8;
	curr_pixel = img->data + (x * i) + (y * img->sz_line);
	if (img->endian == 0)
	{
		while (i--)
			curr_pixel[i] = (color >> (i * 8)) & 0xFF;
	}
	else
	{
		j = 0;
		while (i--)
		{
			curr_pixel[i] = (color >> (j * 8)) & 0xFF;
			j++;
		}
	}
}

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

static t_vertex2i	vertex_proj(t_mlximg *img, t_matrix4 mat,
								t_vector3 vec, t_vertex2i origin)
{
	t_quater	hom;
	t_vector3	ndc;
	t_vertex2i	proj;

	hom = ft_vec3_to_quat(vec, 1.0);
	hom = ft_mat4_postmul_quat(hom, mat);
	ndc = ft_quat_to_vec3(hom);
	proj = ft_viewport_tlc(ndc, origin, img->width, img->height);
	return(proj);
}

static void		draw_map(t_env *env, t_scene *world, t_mlximg *img)
{
	t_matrix4		final_transform;
	t_vertex2i		proj;
	unsigned int	color;
	int				i;
	int				j;

	final_transform = get_mvp_matrix(env->cam, world->mod);
	i = world->height;
	while (i--)
	{
		j = world->width;
		while (j--)
		{
			proj = vertex_proj(img,
								final_transform,
								world->map[i][j],
								ft_to_ver2i(0, 0));
			color = mlx_get_color_value(env->m_env->init_id, 0x00FFFFFF);
			if (proj.x >= 0 && proj.x < img->width
				&& proj.y >= 0 && proj.y < img->height)
				pixel_to_img(img, proj.x, proj.y, color);
		}
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
