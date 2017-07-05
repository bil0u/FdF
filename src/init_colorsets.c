/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_colorsets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 01:16:25 by upopee            #+#    #+#             */
/*   Updated: 2017/07/05 20:58:25 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		set_default(t_colors *sets)
{
	int		i;

	i = 0;
	sets->colors[i][0] = RGB_RED;
	sets->colors[i][1] = RGB_YELLOW;
	sets->colors[i][2] = RGB_WHITE;
	sets->colors[i][3] = RGB_BLUE;
	sets->colors[i][4] = RGB_GREEN;
	sets->nb_colors[i] = 5;
	sets->curr_color[i] = 0;
	sets->marked_alt[i] = 0.000001;
	sets->marked_colorup[i] = 0;
}

static void		set_worldmap(t_colors *sets)
{
	int		i;

	i = 1;
	sets->colors[i][0] = RGB_NAVY_BLUE;
	sets->colors[i][1] = RGB_NAVY_BLUE;
	sets->colors[i][2] = RGB_ROYAL_BLUE;
	sets->colors[i][3] = RGB_ROYAL_BLUE;
	sets->colors[i][4] = RGB_LIGHT_SEA_GREEN;
	sets->colors[i][5] = RGB_YELLOW_GREEN;
	sets->colors[i][6] = RGB_SPRINGGREEN4;
	sets->colors[i][7] = RGB_SPRINGGREEN4;
	sets->colors[i][8] = RGB_BROWN_EARTH;
	sets->colors[i][9] = RGB_BROWN_EARTH;
	sets->colors[i][10] = RGB_WHITE;
	sets->colors[i][11] = RGB_WHITE;
	sets->colors[i][12] = RGB_WHITE;
	sets->colors[i][13] = RGB_WHITE;
	sets->nb_colors[i] = 14;
	sets->curr_color[i] = 0;
	sets->marked_alt[i] = 0.000001;
	sets->marked_colorup[i] = 5;
}

static void		set_test(t_colors *sets)
{
	int		i;

	i = 2;
	sets->colors[i][0] = RGB_WHITE;
	sets->colors[i][1] = RGB_BLUE;
	sets->colors[i][2] = RGB_GREEN;
	sets->colors[i][3] = RGB_YELLOW;
	sets->colors[i][4] = RGB_RED;
	sets->colors[i][5] = RGB_PINK;
	sets->colors[i][6] = RGB_GREY50;
	sets->nb_colors[i] = 7;
	sets->curr_color[i] = 0;
	sets->marked_alt[i] = 0.000001;
	sets->marked_colorup[i] = 3;
}

static void		set_rainbow(t_colors *sets)
{
	int		i;

	i = 3;
	sets->colors[i][0] = 0x442299;
	sets->colors[i][1] = 0x3b0cbd;
	sets->colors[i][2] = 0x3311bb;
	sets->colors[i][3] = 0x4444dd;
	sets->colors[i][4] = 0x11aabb;
	sets->colors[i][5] = 0x12bdb9;
	sets->colors[i][6] = 0x22ccaa;
	sets->colors[i][7] = 0x69d025;
	sets->colors[i][8] = 0xaacc22;
	sets->colors[i][9] = 0xd0c310;
	sets->colors[i][10] = 0xccbb33;
	sets->colors[i][11] = 0xfeae2d;
	sets->colors[i][12] = 0xff9933;
	sets->colors[i][13] = 0xff6644;
	sets->colors[i][14] = 0xff4422;
	sets->colors[i][15] = 0xff3311;
	sets->colors[i][16] = 0xee1100;
	sets->colors[i][17] = 0xf80c12;
	sets->nb_colors[i] = 18;
	sets->curr_color[i] = 0;
	sets->marked_alt[i] = 0.0;
	sets->marked_colorup[i] = 9;
}

void			init_colorsets(t_colors *sets)
{
	set_default(sets);
	set_worldmap(sets);
	set_test(sets);
	set_rainbow(sets);
	sets->curr_set = 0;
}
