/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 02:53:28 by upopee            #+#    #+#             */
/*   Updated: 2017/04/11 03:13:40 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		end_session(t_scene *s, t_mlxenv *e, char *msg, int status)
{
	if (s)
	{
		while (s->nb_lines-- > 0)
			ft_memdel((void **)&(s->tab[s->nb_lines]));
		ft_memdel((void **)&s);
	}
	if (e)
	{
		if (e->win.id)
			mlx_destroy_window(e->mlx_id, e->win.id);
		ft_memdel((void **)&e);
	}
	if (msg)
		ft_putendl_fd(msg, 2);
	exit (status);
}


static void		get_winsize(t_mlxenv *e, t_scene *s)
{
	int		x;
	int		y;

	x = ((s->nb_columns * MLXWIN_DEFAULT_OFFSET) + MLXWIN_MARGEX + 1);
	y = ((s->nb_lines * MLXWIN_DEFAULT_OFFSET) + MLXWIN_MARGEY + 1);
	e->win.sz_x = x > MLXWIN_SIZEX_MAX ? MLXWIN_SIZEX_MAX : x;
	e->win.sz_y = y > MLXWIN_SIZEY_MAX ? MLXWIN_SIZEY_MAX : y;
}

t_mlxenv	*init_mlxenv(t_scene *s)
{
	t_mlxenv	*e;
	char		*n;

	if ((e = ft_memalloc(sizeof(t_mlxenv))) == NULL)
		end_session(s, e, "malloc: cannot allocate memory", EXIT_FAILURE);
	if ((e->mlx_id = mlx_init()) == NULL)
		end_session(s, e, "mlx: cannot connect with server", EXIT_FAILURE);
	get_winsize(e, s);
	n = "> FDF <";
	if (!(e->win.id = mlx_new_window(e->mlx_id, e->win.sz_x, e->win.sz_y, n)))
		end_session(s, e, "mlx: cannot create window", EXIT_FAILURE);
	return (e);
}
