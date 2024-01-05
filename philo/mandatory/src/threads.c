/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:25:04 by marvin            #+#    #+#             */
/*   Updated: 2024/01/05 18:25:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	do_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->status = 0;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, "has taken a fork", 0);
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "has taken a fork", 0);
	pthread_mutex_lock(&philo->lock);
	philo->status = 1;
	philo->time_to_die = get_time() + philo->glob->time_to_die;
	print_message(philo, "is eating", 0);
	philo->eaten_time++;
	ft_usleep(philo->glob->time_to_eat);
	philo->status = 2;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*monitor(void *glob_pointer)
{
	t_glob	*glob;

	glob = (t_glob *) glob_pointer;
	pthread_mutex_lock(&glob->lock);
	while (glob->dead == 0)
	{
		pthread_mutex_unlock(&glob->lock);
		pthread_mutex_lock(&glob->lock);
		if (glob->total_eaten >= glob->philo_num)
			glob->dead = 1;
		pthread_mutex_unlock(&glob->lock);
		ft_usleep(2);
		pthread_mutex_lock(&glob->lock);
	}
	pthread_mutex_unlock(&glob->lock);
	return ((void *)0);
}

void	*supervisor(void *p_pointer)
{
	t_philo	*p;

	p = (t_philo *)p_pointer;
	pthread_mutex_lock(&(p->glob->lock));
	while (p->glob->dead == 0)
	{
		pthread_mutex_unlock(&(p->glob->lock));
		pthread_mutex_lock(&(p->lock));
		if (get_time() >= p->time_to_die && p->status != 1)
			print_message(p, "died", 1);
		if (p->glob->must_eat > 0 && p->eaten_time == p->glob->must_eat)
		{
			p->glob->total_eaten++;
			p->eaten_time++;
		}
		pthread_mutex_unlock(&(p->lock));
		pthread_mutex_lock(&(p->glob->lock));
	}
	pthread_mutex_unlock(&(p->glob->lock));
	return ((void *)0);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	philo->time_to_die = philo->glob->time_to_die + get_time();
	if (pthread_create(&(philo->supervisor), NULL, &supervisor, (void *)philo))
		error_exit(philo->glob);
	pthread_mutex_lock(&(philo->glob->lock));
	while (philo->glob->dead == 0)
	{
		pthread_mutex_unlock(&(philo->glob->lock));
		do_eat(philo);
		print_message(philo, "is sleeping", 0);
		ft_usleep(philo->glob->time_to_sleep);
		print_message(philo, "is thinking", 0);
		ft_usleep(2);
		pthread_mutex_lock(&(philo->glob->lock));
	}
	pthread_mutex_unlock(&(philo->glob->lock));
	if (pthread_join(philo->supervisor, NULL))
		error_exit(philo->glob);
	return ((void *)0);
}
