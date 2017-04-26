/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 21:37:26 by upopee            #+#    #+#             */
/*   Updated: 2017/04/25 19:40:53 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgraphic.h"
#include <stdio.h>
#include <stdlib.h>

# define KEY_ESC 53

int		key_hook(int keycode)
{
	if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	else
	{
		printf("Keycode -> %d\n", keycode);
	}
	return (0);
}

int		main(void)
{
	t_mlxenv	*m_env;
	t_mlxwin	*m_win;

	m_env = init_mlxenv();
	m_win = init_mlxwin(m_env->init_id, 1000, 1000, "Keycode finder");
	mlx_key_hook(m_win->id, &key_hook, NULL);
	mlx_loop(m_env->init_id);
	del_mlxwin(m_env->init_id, m_win);
	del_mlxenv(m_env);
	return (0);
}
