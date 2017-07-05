/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 20:50:18 by upopee            #+#    #+#             */
/*   Updated: 2017/07/05 20:50:30 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			fps_count(t_env *e, void *init_id, void *win_id)
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
