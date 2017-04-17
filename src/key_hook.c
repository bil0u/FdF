/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 20:31:41 by upopee            #+#    #+#             */
/*   Updated: 2017/04/17 20:57:50 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "env_utils.h"
#include "key_hook.h"

int		key_hook(int keycode, t_env *env)
{
	if (keycode == KEY_ESC)
		end_session(env, NULL, EXIT_SUCCESS);
	return (0);
}
