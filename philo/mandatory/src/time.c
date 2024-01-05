/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:30:03 by marvin            #+#    #+#             */
/*   Updated: 2024/01/05 18:30:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_usleep(useconds_t time, t_glob *glob)
{
	u_int64_t	start;

	start = get_time(glob);
	while ((get_time(glob) - start) < time)
		usleep(time / 10);
	return (0);
}

u_int64_t	get_time(t_glob *glob)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit(glob);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}
