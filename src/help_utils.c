/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 17:15:59 by upopee            #+#    #+#             */
/*   Updated: 2017/07/26 19:54:11 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "help_texts.h"

static void		help_more(void *init_id, t_mlxwin *win)
{
	void	*win_id;
	int		width;
	int		height;

	win_id = win->id;
	width = win->width;
	height = win->height;
	text_switches(init_id, win_id, width, height);
	text_modifiers(init_id, win_id, width, height);
	text_others(init_id, win_id, width, height);
}

void			handle_help(void *init_id, t_mlxwin *win, int *keymod)
{
	if (win->width > 800)
		help_more(init_id, win);
	else
	{
		text_console();
		*keymod &= OFF(HELP);
	}
}

void			help_less(void *init_id, t_mlxwin *win)
{
	int		x;
	int		y;

	x = (win->width >> 1) - 75;
	y = win->height - 35;
	mlx_string_put(init_id, win->id, x, y, STR_COLOR, "Press [H] for help");
}
