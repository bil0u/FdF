/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 22:08:57 by upopee            #+#    #+#             */
/*   Updated: 2017/04/30 18:55:27 by upopee           ###   ########.fr       */
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
	if (img->data <= curr_pixel && (curr_pixel + i) < img->limit)
	{
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
}

static t_matrix4	get_model_matrix(t_scene *world)
{
	t_matrix4	scale;
	t_matrix4	rotate;
	t_matrix4	translate;
	t_matrix4	model;

	scale = ft_gen_scale_mat4(world->mod.scale);
	rotate = ft_gen_rotation_mat4(world->mod.rot_angle, world->mod.rot_axis);
	translate = ft_gen_translate_mat4(world->mod.translate);
	model = ft_mat4_mul_mat4(scale, rotate);
	model = ft_mat4_mul_mat4(translate, model);
	return (model);
}

static t_matrix4	get_mvp_matrix(t_env *env)
{
	t_matrix4	model;
	t_matrix4	view;
	t_matrix4	projection;
	t_matrix4	mvp;

	model = get_model_matrix(env->world);
	view = ft_lookat(env->cam, env->world->mod.cam_eye,
					env->world->mod.cam_to, env->world->mod.cam_upv);
	projection = ft_persproj_mat4(env->cam->view_angle * env->world->mod.zoom,
						env->cam->near, env->cam->far, env->cam->aspect_ratio);
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

static void		draw_map(t_env *env)
{
	t_matrix4		final_transform;
	t_vertex2i		proj;
	unsigned int	color;
	int				i;
	int				j;

	final_transform = get_mvp_matrix(env);
	i = env->world->height;
	while (i--)
	{
		j = env->world->width;
		while (j--)
		{
			proj = vertex_proj(env->m_img, final_transform,
									env->world->map[i][j], ft_to_ver2i(0, 0));
			color = mlx_get_color_value(env->m_env->init_id, 0xFFFFFF);
			if (proj.x >= 0 && proj.x < env->m_img->width && proj.y >= 0 && proj.y < env->m_img->height)
				pixel_to_img(env->m_img, proj.x, proj.y, color);
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
	draw_map(env);
	mlx_put_image_to_window(mlx->init_id, win->id, img->id, 0, 0);
	del_mlximg(mlx->init_id, img);
	return (0);
}
