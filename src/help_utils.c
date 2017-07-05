/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 17:15:59 by upopee            #+#    #+#             */
/*   Updated: 2017/07/05 20:50:10 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			help_less(void *init_id, t_mlxwin *win)
{
	int		x;
	int		y;

	x = (win->width >> 1) - 75;
	y = win->height - 35;
	mlx_string_put(init_id, win->id, x, y, STR_COLOR, "Press [H] for help");
}

static void		show_switches(void *init_id, void *win_id, int w, int h)
{
	char	*buff;
	int		x;

	x = (w >> 1) - 590;
	buff = "                                      +";
	mlx_string_put(init_id, win_id, x, h - 145, STR_COLOR, buff);
	buff = "                                      |";
	mlx_string_put(init_id, win_id, x, h - 125, STR_COLOR, buff);
	buff = "+-------------------------------------+";
	mlx_string_put(init_id, win_id, x, h - 105, STR_COLOR, buff);
	buff = "| Z/A > Zoom / Alt modifier mode      |";
	mlx_string_put(init_id, win_id, x, h - 85, STR_COLOR, buff);
	buff = "| R/T > Rotation/Translation mode     |";
	mlx_string_put(init_id, win_id, x, h - 65, STR_COLOR, buff);
	buff = "|  C  > Simple/Pinned/Full color mode |";
	mlx_string_put(init_id, win_id, x, h - 45, STR_COLOR, buff);
	buff = "+-------------------------------------+";
	mlx_string_put(init_id, win_id, x, h - 25, STR_COLOR, buff);
}

static void		show_modifiers(void *init_id, void *win_id, int w, int h)
{
	char	*buff;
	int		x;

	x = (w >> 1) - 200;
	buff = "---------------------------------------";
	mlx_string_put(init_id, win_id, x, h - 145, STR_COLOR, buff);
	buff = "   +/-  > Modify Zoom/Alt value         ";
	mlx_string_put(init_id, win_id, x, h - 125, STR_COLOR, buff);
	buff = " ARROW > Rotate/Translate map          ";
	mlx_string_put(init_id, win_id, x, h - 105, STR_COLOR, buff);
	buff = " SPACE > Next Color/Set                ";
	mlx_string_put(init_id, win_id, x, h - 85, STR_COLOR, buff);
	buff = "  X/V  > Modify pinned alt in curr set ";
	mlx_string_put(init_id, win_id, x, h - 65, STR_COLOR, buff);
	buff = "  DEL  > Reset in original position    ";
	mlx_string_put(init_id, win_id, x, h - 45, STR_COLOR, buff);
	buff = "---------------------------------------";
	mlx_string_put(init_id, win_id, x, h - 25, STR_COLOR, buff);
}

static void		show_others(void *init_id, void *win_id, int w, int h)
{
	char	*buff;
	int		x;

	x = (w >> 1) + 190;
	mlx_string_put(init_id, win_id, x, h - 145, STR_COLOR, "+");
	mlx_string_put(init_id, win_id, x, h - 125, STR_COLOR, "|");
	buff = "+--------------------------------------+";
	mlx_string_put(init_id, win_id, x, h - 105, STR_COLOR, buff);
	buff = "|   D   > Show/Hide debug informations |";
	mlx_string_put(init_id, win_id, x, h - 85, STR_COLOR, buff);
	buff = "|   H   > Hide Help                    |";
	mlx_string_put(init_id, win_id, x, h - 65, STR_COLOR, buff);
	buff = "| Q/ESC > Quit program                 |";
	mlx_string_put(init_id, win_id, x, h - 45, STR_COLOR, buff);
	buff = "+--------------------------------------+";
	mlx_string_put(init_id, win_id, x, h - 25, STR_COLOR, buff);
}

void			help_more(void *init_id, t_mlxwin *win)
{
	void	*win_id;
	int		width;
	int		height;

	win_id = win->id;
	width = win->width;
	height = win->height;
	show_switches(init_id, win_id, width, height);
	show_modifiers(init_id, win_id, width, height);
	show_others(init_id, win_id, width, height);
}
