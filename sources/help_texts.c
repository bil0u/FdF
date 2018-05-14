/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_texts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 17:15:59 by upopee            #+#    #+#             */
/*   Updated: 2017/07/10 04:40:27 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		text_switches(void *init_id, void *win_id, int w, int h)
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

void		text_modifiers(void *init_id, void *win_id, int w, int h)
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

void		text_others(void *init_id, void *win_id, int w, int h)
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

void		text_console(void)
{
	ft_putstr("+---------------------------------------+\n");
	ft_putstr("|  Z/A  > Zoom / Alt modifier mode      |\n");
	ft_putstr("|  R/T  > Rotation/Translation mode     |\n");
	ft_putstr("|   C   > Simple/Pinned/Full color mode |\n");
	ft_putstr("+---------------------------------------+\n");
	ft_putstr("|  +/-  > Modify Zoom/Alt value         |\n");
	ft_putstr("| ARROW > Rotate/Translate map          |\n");
	ft_putstr("| SPACE > Next Color/Set                |\n");
	ft_putstr("|  X/V  > Modify pinned alt in curr set |\n");
	ft_putstr("|  DEL  > Reset in original position    |\n");
	ft_putstr("+---------------------------------------+\n");
	ft_putstr("|   D   > Show/Hide debug informations  |\n");
	ft_putstr("| Q/ESC > Quit program                  |\n");
	ft_putstr("+---------------------------------------+\n");
}
