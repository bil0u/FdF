/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 21:02:39 by upopee            #+#    #+#             */
/*   Updated: 2017/04/04 19:28:12 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "parse_input.h"

int			main(int argc, char **argv)
{
	t_map	*m;

	if (argc != 2)
	{
		ft_putendl_fd("usage : ./fdf [path/to/file]", 2);
		return (-1);
	}
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
	ft_memdel((void **)&m);
	return (0);
}
