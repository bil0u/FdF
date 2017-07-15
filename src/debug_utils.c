/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 20:50:18 by upopee            #+#    #+#             */
/*   Updated: 2017/07/10 05:06:57 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		fps_count(t_env *e, void *init_id, void *win_id)
{
	char	*buff;
	float	current_time;
	float	interval;

	e->nb_frames++;
	buff = e->sbuff;
	current_time = clock() / CLOCKS_PER_SEC;
	interval = current_time - e->last_time;
	if (interval >= FPS_REFRESH_TIME)
	{
		ft_sprintf(buff, "%3d FPS", (int)((float)e->nb_frames / interval));
		e->last_time = current_time;
		e->nb_frames = 0;
	}
	mlx_string_put(init_id, win_id, 10, 10, STR_COLOR, buff);
}

static void		mod_values(char f, t_env *e, void *init_id, void *win_id)
{
	char		*format;
	char		buff[64];
	t_mod		mod;
	int			i;

	mod = e->world->mod;
	i = mod.col.curr_set;
	if (f == 1)
	{
		ft_putstr("+---------------------------------------+\n");
		ft_putstr("| >> DEBUG VALUES                       |\n");
		printf("| Current color set                 %2d  |\n",
													mod.col.curr_set);
		printf("| Pinned altitude             %8.3f  |\n",
													mod.col.marked_alt[i]);
		printf("| Zoom                            %4.2f  |\n", mod.zoom);
		ft_putstr("+---------------------------------------+\n");
		return ;
	}
	format = "Current set: %d |  Pinned alt: %.3f |  Zoom: %.1f";
	sprintf(buff, format, mod.col.curr_set, mod.col.marked_alt[i], mod.zoom);
	mlx_string_put(init_id, win_id, e->m_win->width - 480, 10, STR_COLOR, buff);
}

void			print_debug(t_env *e, void *init_id, void *win_id)
{
	if (e->m_win->width > 550)
		mod_values(0, e, init_id, win_id);
	else
		mod_values(1, e, init_id, win_id);
	fps_count(e, init_id, win_id);
}
