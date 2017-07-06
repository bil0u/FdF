/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_frame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upopee <upopee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 19:27:26 by upopee            #+#    #+#             */
/*   Updated: 2017/07/06 21:20:11 by upopee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		*clear_segment(void *arg)
{
	t_dataseg	*segment;
	t_dataseg	curr;
	int			*data;
	int			bytes_left;

	segment = (t_dataseg *)arg;
	curr.start = segment->start;
	curr.stop = segment->stop;
	bytes_left = curr.stop - curr.start;
	data = (int *)curr.start;
	while (bytes_left >= 4)
	{
		data[0] = 0;
		data++;
		bytes_left -= 4;
	}
	curr.start = (char *)data;
	while (bytes_left > 0)
	{
		curr.start[0] = 0;
		curr.start++;
		bytes_left--;
	}
	pthread_exit(NULL);
}

void			clear_frame(char *frame, int nb_bytes)
{
    t_threads4		thds;
	t_imgdata		data;
	int				left;
	int				quarter;

	left = nb_bytes % 4;
	nb_bytes -= left;
	quarter = (nb_bytes >> 1);
	nb_bytes = quarter % 4;
	left += (nb_bytes << 1);
	quarter = ((quarter - nb_bytes) >> 1);
	data.t0.start = frame;
	data.t0.stop = (frame + quarter);
	data.t1.start = data.t0.stop;
	data.t1.stop = data.t1.start + quarter;
	data.t2.start = data.t1.stop;
	data.t2.stop =  data.t2.start + quarter;
	data.t3.start = data.t2.stop;
	data.t3.stop = data.t3.start + quarter + left;
	pthread_create(&thds.t0, NULL, &clear_segment, (void *)(&data.t0));
	pthread_create(&thds.t1, NULL, &clear_segment, (void *)(&data.t1));
	pthread_create(&thds.t2, NULL, &clear_segment, (void *)(&data.t2));
	pthread_create(&thds.t3, NULL, &clear_segment, (void *)(&data.t3));
	pthread_join(thds.t0, NULL);
	pthread_join(thds.t1, NULL);
	pthread_join(thds.t2, NULL);
	pthread_join(thds.t3, NULL);
}
