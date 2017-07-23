/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 20:50:18 by upopee            #+#    #+#             */
/*   Updated: 2017/07/19 16:15:34 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

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

static void		terminal_debug(t_env *e)
{
	char		*format;
	t_mod		mod;
	int			i;

	mod = e->world->mod;
	i = mod.col.curr_set;
	if (FULL_SET_SET(mod.keymod))
	{
		if (MARKED_SET_SET(mod.keymod))
			format = "| Pinned altitude             %8.3f  |\n";
		else
			format = "| Full colorset mode                    |\n";
	}
	else
		format = "| Single color mode                     |\n";
	ft_putstr("+---------------------------------------+\n");
	ft_putstr("| >> DEBUG VALUES                       |\n");
	printf("| Current color set                 %2d  |\n", mod.col.curr_set);
	printf(format, mod.col.marked_alt[i]);
	printf("| Zoom                            %.3f   |\n", mod.zoom);
	ft_putstr("+---------------------------------------+\n");
}

static void		window_debug(t_env *e, void *init_id, void *win_id)
{
	char		*format;
	char		buff[64];
	t_mod		mod;
	int			i;

	mod = e->world->mod;
	i = mod.col.curr_set;
	if (FULL_SET_SET(mod.keymod))
	{
		if (MARKED_SET_SET(mod.keymod))
			format = "Current set: %1$d |  Pinned alt: %2$.3f |  Zoom: %3$.3f";
		else
			format = "Current set: %1$d |    Full colorset   |  Zoom: %3$.3f";
	}
	else
		format = "Current set: %1$d |   Single color    |  Zoom: %3$.3f";
	sprintf(buff, format, mod.col.curr_set, mod.col.marked_alt[i], mod.zoom);
	mlx_string_put(init_id, win_id, e->m_win->width - 500, 10, STR_COLOR, buff);
}

void			print_debug(t_env *e, void *init_id, void *win_id)
{
	if (e->m_win->width > 550)
		window_debug(e, init_id, win_id);
	else
		terminal_debug(e);
	fps_count(e, init_id, win_id);
}
