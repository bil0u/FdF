/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorsets.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 01:16:25 by upopee            #+#    #+#             */
/*   Updated: 2017/06/29 02:05:54 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		set_default(t_colors *sets)
{
	int		i;

	i = 0;
	sets->colors[i][0] = RGB_NAVY_BLUE;
	sets->colors[i][1] = RGB_ROYAL_BLUE;
	sets->colors[i][2] = RGB_SPRINGGREEN4;
	sets->colors[i][3] = RGB_BROWN_EARTH;
	sets->colors[i][4] = RGB_GREY50;
	sets->colors[i][5] = RGB_WHITE;
	sets->colors[i][6] = RGB_WHITE;
	sets->nb_colors[i] = 7;
	sets->curr_color[i] = 0;
	sets->marked_alt[i] = 0.000001;
	sets->marked_colorup[i] = 2;
}

static void		set_test(t_colors *sets)
{
	int		i;

	i = 1;
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

void			set_colors(t_colors *sets)
{
	set_default(sets);
	set_test(sets);
}
