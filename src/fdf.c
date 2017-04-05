/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 21:02:39 by upopee            #+#    #+#             */
/*   Updated: 2017/04/05 03:39:34 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx_env.h"
#include "parse_input.h"

int			main(int argc, char **argv)
{
	t_mlxenv	*e;
	t_map		*m;

	if (argc != 2)
		end_session(NULL, NULL, "usage : ./fdf [path/to/file]", EXIT_FAILURE);
	m = input_to_map(argv[1]);

#ifdef DEBUG
	{
		int 		i;
		int 		j;
		i = 0;
		while (i < m->nb_lines)
		{
			j = 0;
			while (j < m->nb_columns)
			{
				ft_printf("%d ", m->tab[i][j]);
				j++;
			}
			ft_putendl("");
			i++;
		}
	}
#endif

	e = init_mlxenv(m);
	mlx_loop(e->mlx_id);
	end_session(m, e, NULL, EXIT_SUCCESS);
	return (0);
}
