/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:53:05 by ycontre           #+#    #+#             */
/*   Updated: 2024/01/05 19:57:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	calcul_philo(t_glob *g)
{
	pthread_t	t;
	int			i;

	g->start_time = get_time();
	if (g->must_eat > 0 && pthread_create(&t, NULL, &monitor, g))
		return (error_exit(g));
	i = -1;
	while (++i < g->philo_num)
	{
		pthread_mutex_lock(&(g->lock));
		pthread_mutex_lock(&(g->philo[i].lock));
		if (pthread_create(&(g->philo[i].routine), 0, &routine, &g->philo[i]))
			error_exit(g);
		pthread_mutex_unlock(&(g->lock));
		pthread_mutex_unlock(&(g->philo[i].lock));
		ft_usleep(1);
	}
	i = -1;
	while (++i < g->philo_num)
	{
		if (pthread_join(g->philo[i].routine, NULL))
			error_exit(g);
	}
	if (g->must_eat > 0 && pthread_join(t, NULL))
		error_exit(g);
}

void	one_philo(t_glob *glob)
{
	glob->start_time = get_time();
	if (pthread_create(&(glob->philo[0].routine), NULL, \
		&routine, &glob->philo[0]))
		error_exit(glob);
	pthread_detach(glob->philo[0].routine);
	pthread_mutex_lock(&(glob->lock));
	while (glob->dead == 0)
	{
		pthread_mutex_unlock(&(glob->lock));
		ft_usleep(1);
		pthread_mutex_lock(&(glob->lock));
	}
	pthread_mutex_unlock(&(glob->lock));
	clear_data(glob);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_glob	*glob;

	if (ft_handle_errors(argc, argv) == 0)
		return (0);
	glob = init_glob(argv, argc);
	if (glob->philo_num == 1)
		one_philo(glob);
	calcul_philo(glob);
	clear_data(glob);
	return (0);
}
