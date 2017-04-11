/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 21:02:39 by upopee            #+#    #+#             */
/*   Updated: 2017/04/11 06:55:12 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx_env.h"
#include "parse_input.h"
#include "matrix_utils.h"

int			main(int argc, char **argv)
{
	t_mlxenv	*e;
	t_scene		*s;

	if (argc != 2)
		end_session(NULL, NULL, "usage : ./fdf [path/to/file]", EXIT_FAILURE);
	s = input_to_scene(argv[1]);

#ifdef DEBUG
	{
		int 		i;
		int 		j;
		i = 0;
		ft_putendl("------------");
		while (i < s->nb_lines)
		{
			j = 0;
			while (j < s->nb_columns)
			{
				ft_printf("{%.f,%.f,%.f} ", (s->tab[i][j]).x, (s->tab[i][j]).y, (s->tab[i][j]).z);
				j++;
			}
			ft_putendl("");
			i++;
		}
		ft_putendl("------------");
	}
#endif

	t_matrix4f	m_id;

	m_id = ft_matrix4f_id();
	apply_matrix4f_to_scene(&m_id, s);

#ifdef DEBUG
	{
		int 		i;
		int 		j;
		i = 0;
		ft_putendl("------------");
		while (i < s->nb_lines)
		{
			j = 0;
			while (j < s->nb_columns)
			{
				ft_printf("{%.f,%.f,%.f} ", (s->tab[i][j]).x, (s->tab[i][j]).y, (s->tab[i][j]).z);
				j++;
			}
			ft_putendl("");
			i++;
		}
		ft_putendl("------------");
	}
#endif

	e = init_mlxenv(s);
	mlx_loop(e->mlx_id);
	end_session(s, e, NULL, EXIT_SUCCESS);
	return (0);
}
