/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 20:33:09 by upopee            #+#    #+#             */
/*   Updated: 2017/07/05 18:56:46 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_HOOK_H
# define KEY_HOOK_H

int		key_press(int keycode, int *keys);
int		key_release(int keycode, int *keys);
int		loop_hook(t_env *env);

#endif
