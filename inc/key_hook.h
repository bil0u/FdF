/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 20:33:09 by upopee            #+#    #+#             */
/*   Updated: 2017/07/01 18:31:52 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_HOOK_H
# define KEY_HOOK_H

# define KEY_0 29
# define KEY_1 18
# define KEY_2 19
# define KEY_3 20
# define KEY_4 21
# define KEY_5 23
# define KEY_6 22
# define KEY_7 26
# define KEY_8 28
# define KEY_9 25

# define KEY_ESC 53
# define KEY_DEL 51
# define KEY_ENTER 36
# define KEY_SHIFT_LEFT 257
# define KEY_SHIFT_RIGHT 258
# define KEY_CAPSLOCK 272
# define KEY_SPACE 49
# define KEY_ALT_LEFT 261
# define KEY_ALT_RIGHT 262
# define KEY_CMD_LEFT 259
# define KEY_CMD_RIGHT 260
# define KEY_CTRL 256
# define KEY_FN 279
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define KEY_A 12
# define KEY_B 11
# define KEY_C 8
# define KEY_D 2
# define KEY_E 14
# define KEY_F 3
# define KEY_G 5
# define KEY_H 4
# define KEY_I 34
# define KEY_J 38
# define KEY_K 40
# define KEY_L 37
# define KEY_M 41
# define KEY_N 45
# define KEY_O 31
# define KEY_P 35
# define KEY_Q 0
# define KEY_R 15
# define KEY_S 1
# define KEY_T 17
# define KEY_U 32
# define KEY_V 9
# define KEY_W 6
# define KEY_X 7
# define KEY_Y 16
# define KEY_Z 13

# define KEY_PLUS 44
# define KEY_MINUS 24

int		key_press(int keycode, t_keymod *key);
int		key_release(int keycode, t_keymod *key);
int		loop_hook(t_env *env);

#endif
